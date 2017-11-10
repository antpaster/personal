package ru.netris.mobistreamer.modules.login.rest;

import java.util.List;

import retrofit2.Call;
import retrofit2.Retrofit;
import retrofit2.http.Path;

/**
 * Created by ps on 25.06.17.
 */

public class LoginService implements LoginServiceInterface {

    public LoginService() {
        Retrofit retrofit = new Retrofit.Builder()
                .baseUrl("http://172.16.0.26:7070")
                .build();

        LoginServiceInterface service = retrofit.create(LoginServiceInterface.class);
    }

    @Override
    public Call<List<String>> requestAuth(@Path("user") String user, @Path("password") String password) {
        return null;
    }

    @Override
    public Call<List<String>> requestRecordingSettings() {
        return null;
    }
}
