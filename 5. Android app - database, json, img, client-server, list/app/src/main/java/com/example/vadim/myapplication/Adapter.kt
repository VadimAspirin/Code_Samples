package com.example.vadim.myapplication

import android.support.v7.widget.RecyclerView
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import android.widget.TextView
import com.squareup.picasso.Picasso
import kotlinx.android.synthetic.main.unit_child.view.*

class Adapter(items: ArrayList<Content>) : RecyclerView.Adapter<Adapter.ViewHolder>() {

    var list = items

    override fun onCreateViewHolder(parent: ViewGroup?, viewType: Int): ViewHolder {
        return ViewHolder(LayoutInflater.from(parent?.context).inflate(R.layout.unit_child, parent, false))
    }

    override fun getItemCount(): Int {
        return list.size
    }

    override fun onBindViewHolder(holder: ViewHolder?, position: Int) {
        holder?.textViewName?.text = list[position].name
        holder?.textViewYear?.text = list[position].year
        holder?.textViewCountry?.text = list[position].country
        holder?.textViewDescription?.text = list[position].description
        holder?.textViewGenre?.text = list[position].genre
        Picasso.get()
                .load(list[position].picture)
                .into(holder?.imageView)
    }

    class ViewHolder(itemView: View?) : RecyclerView.ViewHolder(itemView) {
        var textViewName: TextView? = itemView?.textViewName
        var textViewYear: TextView? = itemView?.textViewYear
        var textViewCountry: TextView? = itemView?.textViewCountry
        var textViewDescription: TextView? = itemView?.textViewDescription
        var textViewGenre: TextView? = itemView?.textViewGenre
        var imageView: ImageView? = itemView?.imageView
    }

}