package com.happyworldgames.carclimatecontrol.adapter

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.SeekBar
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.happyworldgames.carclimatecontrol.R
import kotlin.collections.ArrayList

class MainRecyclerViewAdapter(private var viewItemList: ArrayList<ViewItem> = arrayListOf()) : RecyclerView.Adapter<MainRecyclerViewAdapter.MainViewHolder>() {

    override fun getItemViewType(position: Int): Int {
        return viewItemList[position].viewType
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): MainViewHolder {
        val view = LayoutInflater.from(parent.context).inflate(viewType, parent, false)
        return when(viewType) {
            R.layout.text_view_holder -> TextViewHolder(view)
            R.layout.seek_bar_holder -> SeekBarHolder(view)
            else -> throw Throwable("Error not found view type")
        }
    }

    override fun onBindViewHolder(holder: MainViewHolder, position: Int) {
        val viewItem = viewItemList[position]
        holder.onBind(viewItem)
    }

    override fun getItemCount(): Int = viewItemList.size

    fun setViewList(viewItemList: ArrayList<ViewItem>) {
        this.viewItemList = viewItemList
    }

    abstract class MainViewHolder(view: View) : RecyclerView.ViewHolder(view) {
        abstract fun onBind(viewItem: ViewItem)
    }

    class TextViewHolder(view: View) : MainViewHolder(view) {
        private val textView: TextView = view.findViewById(R.id.textView)

        override fun onBind(viewItem: ViewItem) {
            textView.text = viewItem.data as String
        }
    }
    class SeekBarHolder(view: View) : MainViewHolder(view) {
        private val seekBar: SeekBar = view.findViewById(R.id.seekBar)

        override fun onBind(viewItem: ViewItem) {
            val data = viewItem.data as SeekBarData

            seekBar.progress = data.progress
        }
    }

    data class ViewItem(
        val viewType: Int,              // R.layout
        val holderClass: Class,     // Holder for work
        var data: Any                   // Data for Holder
    )

    data class SeekBarData(
        val progress: Int,
        val color: Int
    )

}