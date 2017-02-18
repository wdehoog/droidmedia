/*
 * Copyright (C) 2014-2015 Jolla Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Authored by: Mohammed Hassan <mohammed.hassan@jolla.com>
 */

#define LOG_NDEBUG 0
#define LOG_TAG "minisfservice"

#include "allocator.h"
#include <ui/GraphicBuffer.h>

DroidMediaAllocator::DroidMediaAllocator() :
    m_size(0), prev_w(0), prev_h(0)
{

}

DroidMediaAllocator::~DroidMediaAllocator()
{

}

#if defined(BACON_VDEC_HACK)

#ifndef MSM_MEDIA_ALIGN
#define MSM_MEDIA_ALIGN(__sz, __align) (((__sz) + (__align-1)) & (~(__align-1)))
#endif

int DroidMediaAllocator::computeBufferSize(uint32_t width, uint32_t height) {
  // copied from msm_media_info.h 
  // assumed Pixelformat = 0x7FA30C04

  const unsigned int extra_size = 4096; // VENUS_EXTRADATA_SIZE(width, height);
  unsigned int uv_alignment;
  unsigned int size = 0;
  unsigned int y_plane, uv_plane, y_stride, uv_stride, y_sclines, uv_sclines;

  if (!width || !height)
    goto invalid_input;

  y_stride = MSM_MEDIA_ALIGN(width, 128);  // VENUS_Y_STRIDE(int color_fmt, int width)
  uv_stride = MSM_MEDIA_ALIGN(width, 128); // VENUS_UV_STRIDE(int color_fmt, int width)
  y_sclines = MSM_MEDIA_ALIGN(height, 32); // VENUS_Y_SCANLINES(int color_fmt, int height)
  uv_sclines = MSM_MEDIA_ALIGN(((height + 1) >> 1), 16); // VENUS_UV_SCANLINES(int color_fmt, int height)

  uv_alignment = 4096;
  y_plane = y_stride * y_sclines;
  uv_plane = uv_stride * uv_sclines + uv_alignment;
  size = y_plane + uv_plane + extra_size;
  size = MSM_MEDIA_ALIGN(size, 4096);

invalid_input:
  return size;
}
#endif


android::sp<android::GraphicBuffer>
DroidMediaAllocator::createGraphicBuffer(uint32_t w, uint32_t h,
                                         android::PixelFormat format, uint32_t usage,
                                         android::status_t* error)
{
    int s;
ALOGE("DroidMediaAllocator::createGraphicBuffer(w=%d, h=%d, f=0x%X, u=%d) m_size=%d", w, h, format, usage, m_size);
    // Copied from SurfaceFlinger.cpp
    android::sp<android::GraphicBuffer> graphicBuffer;

#if defined(BACON_VDEC_HACK)
    // For video playing (decoding) new GraphicBuffer will create a smaller
    // buffer then the omx_vdec expects (even though it seems to be big enough)
    // and thus rejects it and so video playing will not work.
    //
    // For the camera however the buffer size will be ok and giving it a larger
    // value results in images with a green bar.
    //
    // By enabling (in CM-12.1) most of the code that is disabled using
    // #ifdef QCOM_BSP_LEGACY the required buffer size is set with a call
    // to setGraphicBufferSize when decoding for playing video starts.
    // At the end a call will reset it to 0.
    // For the camera this does not seem to happen.
    //
    // We still need way to detect the two different situations.
    // Relying on m_size being set might not be enough.
    // And what if both processes happen simultanously?
    // Then m_size will still be set only once but we do not know
    // which GraphicBuffer constructor to call.
    //
    // It looks like:
    //   play video          : format == 0x7FA30C04, m_size > 0
    //   video preview camera: format == 0x11, m_size == 0
    //   video record camera : format == 0x7FA30C04, m_size == 0
    //
    //   0x7FA30C04 = HAL_PIXEL_FORMAT_YCbCr_420_SP_VENUS?
    //   0x11       = HAL_PIXEL_FORMAT_YCrCb_420_SP
    if(m_size != 0 && format == 0x7FA30C04) {
      // assume video decoding
      ALOGE("DroidMediaAllocator use set buffersize m_size=%d", m_size);
      graphicBuffer = new android::GraphicBuffer(w, h, format, usage, m_size);
    //} else if(format == 0x7FA30C04) {
    //  // assume video decoding
    //  s = computeBufferSize(w, h);
    //  ALOGE("DroidMediaAllocator compute buffersize s=%d", s);
    //  graphicBuffer = new android::GraphicBuffer(w, h, format, usage, s);
    } else if(m_size > 0) { 
      // not expected to happen but assume video decoding
      s = computeBufferSize(w, h);
      ALOGE("DroidMediaAllocator verify buffersize m_size=%d, s=%d", m_size, s);
      if(m_size> s)
        s = m_size;
      graphicBuffer = new android::GraphicBuffer(w, h, format, usage, s);
    } else {
      // no size set, default behaviour, (probably the camera)
      ALOGE("DroidMediaAllocator leave buffer size to libstagefright");
      graphicBuffer = new android::GraphicBuffer(w, h, format, usage);
    }
#elif (ANDROID_MAJOR == 4 && ANDROID_MINOR >= 2) || ANDROID_MAJOR == 5
    graphicBuffer = new android::GraphicBuffer(w, h, format, usage);
#else
    graphicBuffer = new android::GraphicBuffer(w, h, format, usage, m_size);
#endif
    android::status_t err = graphicBuffer->initCheck();

    *error = err;

    if (err != android::NO_ERROR || graphicBuffer->handle == 0) {
        ALOGE("DroidMediaAllocator::createGraphicBuffer(w=%d, h=%d) "
              "failed (%s), handle=%p, format=0x%x, usage=0x%x, size=%d",
              w, h, strerror(-err), graphicBuffer->handle, format, usage, m_size);
        return 0;
    }

    return graphicBuffer;
}

void DroidMediaAllocator::setGraphicBufferSize(int size)
{
ALOGE("DroidMediaAllocator::setGraphicBufferSize(size=%d)", size);
    m_size = size;
}
