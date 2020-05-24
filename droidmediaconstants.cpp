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

#include "droidmediaconstants.h"
#include <system/camera.h>
#include <system/graphics.h>
#include <OMX_IVCommon.h>

extern "C" {

void droid_media_camera_constants_init(DroidMediaCameraConstants *c)
{
    c->CAMERA_FRAME_CALLBACK_FLAG_ENABLE_MASK = CAMERA_FRAME_CALLBACK_FLAG_ENABLE_MASK;
    c->CAMERA_FRAME_CALLBACK_FLAG_ONE_SHOT_MASK = CAMERA_FRAME_CALLBACK_FLAG_ONE_SHOT_MASK;
    c->CAMERA_FRAME_CALLBACK_FLAG_COPY_OUT_MASK = CAMERA_FRAME_CALLBACK_FLAG_COPY_OUT_MASK;
    c->CAMERA_FRAME_CALLBACK_FLAG_NOOP = CAMERA_FRAME_CALLBACK_FLAG_NOOP;
    c->CAMERA_FRAME_CALLBACK_FLAG_CAMCORDER = CAMERA_FRAME_CALLBACK_FLAG_CAMCORDER;
    c->CAMERA_FRAME_CALLBACK_FLAG_CAMERA = CAMERA_FRAME_CALLBACK_FLAG_CAMERA;
    c->CAMERA_FRAME_CALLBACK_FLAG_BARCODE_SCANNER = CAMERA_FRAME_CALLBACK_FLAG_BARCODE_SCANNER;
    c->CAMERA_MSG_ERROR = CAMERA_MSG_ERROR;
    c->CAMERA_MSG_SHUTTER = CAMERA_MSG_SHUTTER;
    c->CAMERA_MSG_FOCUS = CAMERA_MSG_FOCUS;
    c->CAMERA_MSG_ZOOM = CAMERA_MSG_ZOOM;
    c->CAMERA_MSG_PREVIEW_FRAME = CAMERA_MSG_PREVIEW_FRAME;
    c->CAMERA_MSG_VIDEO_FRAME = CAMERA_MSG_VIDEO_FRAME;
    c->CAMERA_MSG_POSTVIEW_FRAME = CAMERA_MSG_POSTVIEW_FRAME;
    c->CAMERA_MSG_RAW_IMAGE = CAMERA_MSG_RAW_IMAGE;
    c->CAMERA_MSG_COMPRESSED_IMAGE = CAMERA_MSG_COMPRESSED_IMAGE;
    c->CAMERA_MSG_RAW_IMAGE_NOTIFY = CAMERA_MSG_RAW_IMAGE_NOTIFY;
    c->CAMERA_MSG_PREVIEW_METADATA = CAMERA_MSG_PREVIEW_METADATA;
    c->CAMERA_MSG_FOCUS_MOVE = CAMERA_MSG_FOCUS_MOVE;
    c->CAMERA_MSG_ALL_MSGS = CAMERA_MSG_ALL_MSGS;
    c->CAMERA_CMD_START_SMOOTH_ZOOM = CAMERA_CMD_START_SMOOTH_ZOOM;
    c->CAMERA_CMD_STOP_SMOOTH_ZOOM = CAMERA_CMD_STOP_SMOOTH_ZOOM;
    c->CAMERA_CMD_SET_DISPLAY_ORIENTATION = CAMERA_CMD_SET_DISPLAY_ORIENTATION;
    c->CAMERA_CMD_ENABLE_SHUTTER_SOUND = CAMERA_CMD_ENABLE_SHUTTER_SOUND;
    c->CAMERA_CMD_PLAY_RECORDING_SOUND = CAMERA_CMD_PLAY_RECORDING_SOUND;
    c->CAMERA_CMD_START_FACE_DETECTION = CAMERA_CMD_START_FACE_DETECTION;
    c->CAMERA_CMD_STOP_FACE_DETECTION = CAMERA_CMD_STOP_FACE_DETECTION;
    c->CAMERA_CMD_ENABLE_FOCUS_MOVE_MSG = CAMERA_CMD_ENABLE_FOCUS_MOVE_MSG;
    c->CAMERA_CMD_PING = CAMERA_CMD_PING;
    c->CAMERA_ERROR_UNKNOWN = CAMERA_ERROR_UNKNOWN;
    c->CAMERA_ERROR_RELEASED = CAMERA_ERROR_RELEASED;
    c->CAMERA_ERROR_SERVER_DIED = CAMERA_ERROR_SERVER_DIED;
    c->CAMERA_FACE_DETECTION_HW = CAMERA_FACE_DETECTION_HW;
    c->CAMERA_FACE_DETECTION_SW = CAMERA_FACE_DETECTION_SW;
}

void droid_media_pixel_format_constants_init(DroidMediaPixelFormatConstants *c)
{
  c->HAL_PIXEL_FORMAT_RGBA_8888 = HAL_PIXEL_FORMAT_RGBA_8888;
  c->HAL_PIXEL_FORMAT_RGBX_8888 = HAL_PIXEL_FORMAT_RGBX_8888;
  c->HAL_PIXEL_FORMAT_RGB_888 = HAL_PIXEL_FORMAT_RGB_888;
  c->HAL_PIXEL_FORMAT_RGB_565 = HAL_PIXEL_FORMAT_RGB_565;
  c->HAL_PIXEL_FORMAT_BGRA_8888 = HAL_PIXEL_FORMAT_BGRA_8888;
  c->HAL_PIXEL_FORMAT_YV12 = HAL_PIXEL_FORMAT_YV12;
#if ANDROID_MAJOR < 6
  c->HAL_PIXEL_FORMAT_RAW_SENSOR = HAL_PIXEL_FORMAT_RAW_SENSOR;
#else
  c->HAL_PIXEL_FORMAT_RAW_SENSOR = HAL_PIXEL_FORMAT_RAW16;
#endif
  c->HAL_PIXEL_FORMAT_YCrCb_420_SP = HAL_PIXEL_FORMAT_YCrCb_420_SP;
  c->HAL_PIXEL_FORMAT_YCbCr_422_SP = HAL_PIXEL_FORMAT_YCbCr_422_SP;
  c->HAL_PIXEL_FORMAT_YCbCr_422_I = HAL_PIXEL_FORMAT_YCbCr_422_I;
  c->QOMX_COLOR_FormatYUV420PackedSemiPlanar32m = 0x7FA30C04;
  c->QOMX_COLOR_FormatYUV420PackedSemiPlanar64x32Tile2m8ka = 0x7FA30C03;
}

void droid_media_colour_format_constants_init(DroidMediaColourFormatConstants *c)
{
  c->QOMX_COLOR_FormatYUV420PackedSemiPlanar32m = 0x7FA30C04;
  c->QOMX_COLOR_FormatYUV420PackedSemiPlanar64x32Tile2m8ka = 0x7FA30C03;
  c->OMX_COLOR_FormatYUV420Planar = OMX_COLOR_FormatYUV420Planar;
  c->OMX_COLOR_FormatYUV420PackedPlanar = OMX_COLOR_FormatYUV420PackedPlanar;
  c->OMX_COLOR_FormatYUV420SemiPlanar = OMX_COLOR_FormatYUV420SemiPlanar;
  c->OMX_COLOR_FormatYUV422SemiPlanar = OMX_COLOR_FormatYUV422SemiPlanar;
  c->OMX_COLOR_FormatL8 = OMX_COLOR_FormatL8;
  c->OMX_COLOR_FormatYCbYCr = OMX_COLOR_FormatYCbYCr;
  c->OMX_COLOR_FormatYCrYCb = OMX_COLOR_FormatYCrYCb;
  c->OMX_COLOR_FormatCbYCrY = OMX_COLOR_FormatCbYCrY;
  c->OMX_COLOR_Format32bitARGB8888 = OMX_COLOR_Format32bitARGB8888;
  c->OMX_COLOR_Format32bitBGRA8888 = OMX_COLOR_Format32bitBGRA8888;
  c->OMX_COLOR_Format16bitRGB565 = OMX_COLOR_Format16bitRGB565;
  c->OMX_COLOR_Format16bitBGR565 = OMX_COLOR_Format16bitBGR565;
}

};
