package com.example.vadim.myapplication

import kotlinx.coroutines.experimental.CommonPool
import kotlinx.coroutines.experimental.Deferred
import kotlinx.coroutines.experimental.async
import kotlin.coroutines.experimental.CoroutineContext

fun saveContent(
        app: App,
        content: List<Content>,
        coroutineContext: CoroutineContext = CommonPool
): Deferred<Unit> = async(coroutineContext) {
    app.database.contentDao().insertAll(content)
}