package com.example.vadim.myapplication

import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.v7.widget.GridLayoutManager
import android.support.v7.widget.LinearLayoutManager
import android.support.v7.widget.RecyclerView
import android.view.View
import android.widget.Toast
import kotlinx.coroutines.experimental.android.UI
import kotlinx.coroutines.experimental.launch

class MainActivity : AppCompatActivity() {

    fun onClickAddNewContent(v: View) {
        val intent = Intent(this, AddContentActivity::class.java)
        startActivity(intent)
        //Toast.makeText(this, "Зачем вы нажали?", Toast.LENGTH_SHORT).show();
    }

    fun onClickReloadContent(v: View) {
        val recyclerView: RecyclerView = findViewById(R.id.recyclerView)
        val content = Content.List()

        launch(UI) {
            /*val cachedContents = loadingContentFromCache(application as App).await()
            if (cachedContents.isNotEmpty()) {
                content.addAll(cachedContents)
                recyclerView.adapter = Adapter(content)
            } else {
              */
            val serverContentJob = loadingContentFromServer()
            serverContentJob.start()
            val serverContent = serverContentJob.await()
            saveContent(application as App, serverContent)
            content.addAll(serverContent)
            recyclerView.adapter = Adapter(content)
            // }
        }
    }


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val recyclerView: RecyclerView = findViewById(R.id.recyclerView) //!!!
        recyclerView.layoutManager = LinearLayoutManager(this)
        //recyclerView.layoutManager = GridLayoutManager(this, 1)

        val content = Content.List() //!!!
        //recyclerView.adapter = Adapter(content)

        launch(UI) {
            val cachedContents = loadingContentFromCache(application as App).await()
            if (cachedContents.isNotEmpty()) {
                content.addAll(cachedContents)
                recyclerView.adapter = Adapter(content)
            } else {
                val serverContentJob = loadingContentFromServer()
                serverContentJob.start()
                val serverContent = serverContentJob.await()
                saveContent(application as App, serverContent)
                content.addAll(serverContent)
                recyclerView.adapter = Adapter(content)
            }
        }
    }
}