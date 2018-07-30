package com.example.vadim.myapplication

import android.arch.persistence.room.Dao
import android.arch.persistence.room.Insert
import android.arch.persistence.room.Query

@Dao
interface ContentDao {

    @Query("SELECT * FROM Content")
    fun getAll(): List<Content>

    @Insert
    fun insertAll(Content: List<Content>)

    @Query("DELETE FROM Content")
    fun deleteAll()
}