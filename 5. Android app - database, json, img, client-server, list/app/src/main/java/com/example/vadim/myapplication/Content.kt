package com.example.vadim.myapplication

import android.arch.persistence.room.Entity
import android.arch.persistence.room.PrimaryKey

@Entity
data class Content(
        val name: String,
        val genre: String,
        val description: String,
        @PrimaryKey
        val picture: String,
        val country: String,
        val year: String
)  {
    class List : ArrayList<Content>()
}