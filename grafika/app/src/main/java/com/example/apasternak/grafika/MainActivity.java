<?xml version="1.0" encoding="utf-8"?>
<!--
        Copyright 2013 Google Inc. All rights reserved.

        Licensed under the Apache License, Version 2.0 (the "License");
        you may not use this file except in compliance with the License.
        You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

        Unless required by applicable law or agreed to in writing, software
        distributed under the License is distributed on an "AS IS" BASIS,
        WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
        See the License for the specific language governing permissions and
        limitations under the License.
        -->

<manifest xmlns:android="http://schemas.android.com/apk/res/android"
        package="com.android.grafika"
        android:versionCode="33"
        android:versionName="1.0" >

<uses-sdk
        android:minSdkVersion="18"
        android:targetSdkVersion="18" />

<uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" />
<uses-permission android:name="android.permission.CAMERA" />

<uses-feature android:glEsVersion="0x00020000" android:required="true" />

<application
        android:allowBackup="true"
                android:icon="@drawable/ic_launcher"
                android:label="@string/app_name"
                android:theme="@style/AppTheme" >
<!-- android:theme="@android:style/Theme.DeviceDefault.Light.NoActionBar" > -->
<activity
            android:name="com.android.grafika.MainActivity"
                    android:label="@string/app_name" >
<intent-filter>
<action android:name="android.intent.action.MAIN" />

<category android:name="android.intent.category.LAUNCHER" />
</intent-filter>
</activity>
<activity
            android:name="com.android.grafika.ReadPixelsActivity"
                    android:label="@string/title_activity_read_pixels" >
</activity>
<activity
            android:name="com.android.grafika.PlayMovieActivity"
                    android:label="@string/title_activity_play_movie" >
</activity>
<activity
            android:name="com.android.grafika.LiveCameraActivity"
                    android:label="@string/title_activity_live_camera" >
</activity>
<activity
            android:name="com.android.grafika.CameraCaptureActivity"
                    android:label="@string/title_activity_camera_capture" >
</activity>
<activity
            android:name="com.android.grafika.TextureViewGLActivity"
                    android:label="@string/title_activity_texture_view_gl" >
</activity>
<activity
            android:name="com.android.grafika.TextureViewCanvasActivity"
                    android:label="@string/title_activity_texture_view_canvas" >
</activity>
<activity
            android:name="com.android.grafika.RecordFBOActivity"
                    android:label="@string/title_activity_record_fbo"
                    android:theme="@android:style/Theme.NoTitleBar.Fullscreen" >

<!-- android:screenOrientation="landscape" -->
<!--
        Without the NoTitleBar theme, the widgets are partially transparent,
        and the SurfaceView colors bleed through.  Not sure why that is.
        -->
<!-- android:theme="@android:style/Theme.NoTitleBar.Fullscreen" -->
</activity>
<activity
            android:name="com.android.grafika.ChorTestActivity"
                    android:label="@string/title_activity_chor_test" >
</activity>
<activity
            android:name="com.android.grafika.DoubleDecodeActivity"
                    android:label="@string/title_activity_double_decode" >
</activity>
<activity
            android:name="com.android.grafika.ContinuousCaptureActivity"
                    android:label="@string/title_activity_continuous_capture" >
</activity>
<activity
            android:name="com.android.grafika.SoftInputSurfaceActivity"
                    android:label="@string/title_activity_soft_input_surface" >
</activity>
<activity
            android:name="com.android.grafika.HardwareScalerActivity"
                    android:label="@string/title_activity_hardware_scaler"
                    android:theme="@android:style/Theme.NoTitleBar.Fullscreen" >
</activity>
<activity
            android:name="com.android.grafika.GlesInfoActivity"
                    android:label="@string/title_activity_gles_info" >
</activity>
<activity
            android:name="com.android.grafika.PlayMovieSurfaceActivity"
                    android:label="@string/title_activity_play_movie_surface" >
</activity>
<activity
            android:name="com.android.grafika.MultiSurfaceActivity"
                    android:label="@string/title_activity_multi_surface_test"
                    android:theme="@android:style/Theme.Holo" >
</activity>
<activity
            android:name="com.android.grafika.CodecOpenActivity"
                    android:label="@string/title_activity_codec_open" >
</activity>
<activity
            android:name="com.android.grafika.TextureUploadActivity"
                    android:label="@string/title_activity_texture_upload" >
</activity>
<activity
            android:name="com.android.grafika.ColorBarActivity"
                    android:label="@string/title_color_bar"
                    android:theme="@android:style/Theme.NoTitleBar.Fullscreen" >
</activity>
<activity
            android:name="com.android.grafika.ScheduledSwapActivity"
                    android:label="@string/title_scheduled_swap"
                    android:theme="@android:style/Theme.Black" >
</activity>
<activity
            android:name="com.android.grafika.TextureFromCameraActivity"
                    android:label="@string/title_texture_from_camera"
                    android:theme="@android:style/Theme.NoTitleBar.Fullscreen" >
</activity>
</application>

</manifest>
