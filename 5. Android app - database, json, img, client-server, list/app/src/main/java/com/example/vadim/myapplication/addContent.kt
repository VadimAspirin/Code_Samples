package com.example.vadim.myapplication

import com.google.gson.Gson
import kotlinx.coroutines.experimental.CommonPool
import kotlinx.coroutines.experimental.Deferred
import kotlinx.coroutines.experimental.async
import okhttp3.*
import kotlin.coroutines.experimental.CoroutineContext

fun addContentToServer(
        content: Content,
        coroutineContext: CoroutineContext = CommonPool
): Deferred<String> = async(coroutineContext) {

    val httpClient = OkHttpClient()

    val JSON = MediaType.parse("application/json; charset=utf-8")
    val formBody = RequestBody.create(JSON, Gson().toJson(content))

    val request = Request.Builder()
            .url("http://85.143.216.90:8082/films/")
            .addHeader("Content-Type", "application/json")
            .put(formBody)
            .build()

    httpClient.newCall(request).execute().use {
        it.body()!!.string()
    }
}