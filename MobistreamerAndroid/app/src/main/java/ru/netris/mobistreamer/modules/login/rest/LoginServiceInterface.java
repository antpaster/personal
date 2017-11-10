package ru.netris.mobistreamer.modules.login.rest;

import java.util.List;

import retrofit2.Call;
import retrofit2.http.GET;
import retrofit2.http.Headers;
import retrofit2.http.POST;
import retrofit2.http.Path;

/**
 * Created by ps on 25.06.17.
 */

public interface LoginServiceInterface {

    @Headers({
            "Content-Type:application/json",
            "X-Requested-With:XMLHttpRequest",
            "X-Auth-Source:NETRIS-MOBILE-STREAMER"
    })
    @POST("/mobile/auth/ajax?j_username={user}&j_password={password}&_spring_security_remember_me=true")
    Call<List<String>> requestAuth(@Path("user") String user, @Path("password") String password);

    @GET("/mobistream/recording/settings")
    Call<List<String>> requestRecordingSettings();

}
