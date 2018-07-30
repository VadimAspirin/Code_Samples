package com.example.vadim.myapplication

import android.arch.persistence.room.Database
import android.arch.persistence.room.RoomDatabase

@Database(entities = [Content::class], version = 1)
abstract class GalleryDatabase : RoomDatabase() {

    abstract fun contentDao(): ContentDao
}