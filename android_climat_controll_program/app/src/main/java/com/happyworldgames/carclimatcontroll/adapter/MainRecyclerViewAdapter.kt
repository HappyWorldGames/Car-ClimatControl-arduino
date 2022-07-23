package com.happyworldgames.carclimatcontroll.adapter

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.happyworldgames.carclimatcontroll.R
import java.util.*
import kotlin.collections.ArrayList

class MainRecyclerViewAdapter(var viewList: ArrayList<ViewItem>) : RecyclerView.Adapter<RecyclerView.ViewHolder>() {

    override fun getItemViewType(position: Int): Int {
        return viewList[position].viewType
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): RecyclerView.ViewHolder {
        val view = LayoutInflater.from(parent.context).inflate(viewType, parent, false)
        return when(viewType) {
            R.layout.text_view_holder -> TextViewHolder(view)
            else -> throw Throwable("Error not found view type")
        }
    }

    override fun onBindViewHolder(holder: RecyclerView.ViewHolder, position: Int) {
        val viewData = viewList[position]

    }

    override fun getItemCount(): Int = viewList.size

    class TextViewHolder(view: View) : RecyclerView.ViewHolder(view) {
        val textViewHolder = view.findViewById<TextView>(R.id.textView)
    }

    data class ViewItem(
        val viewType: Int,      // R.layout
        var data: Objects
        )

}