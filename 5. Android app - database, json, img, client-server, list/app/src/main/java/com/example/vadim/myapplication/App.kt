package com.example.vadim.myapplication

import android.app.Application
import android.arch.persistence.room.Room

class App : Application() {

    lateinit var database: GalleryDatabase

    override fun onCreate() {
        super.onCreate()
        database = Room.databaseBuilder(this, GalleryDatabase::class.java, "gallery").build()
    }
}