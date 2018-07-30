package com.example.vadim.myapplication

import com.google.gson.Gson
import kotlinx.coroutines.experimental.CommonPool
import kotlinx.coroutines.experimental.Deferred
import kotlinx.coroutines.experimental.async
import okhttp3.OkHttpClient
import okhttp3.Request
import kotlin.coroutines.experimental.CoroutineContext

fun loadingContentFromServer(
        coroutineContext: CoroutineContext = CommonPool
): Deferred<List<Content>> = async(coroutineContext) {
    // Создать клиент для HTTP запросов
    val httpClient = OkHttpClient()

    // Создать запрос
    val request = Request.Builder()
            .url("http://85.143.216.90:8082/films/")
            .build()

    httpClient.newCall(request).execute().use {
        Gson().fromJson(it.body()!!.string(), Content.List::class.java)
    }
}

fun loadingContentFromCache(
        app: App,
        coroutineContext: CoroutineContext = CommonPool
): Deferred<List<Content>> = async(coroutineContext) {
    app.database.contentDao().getAll()
}