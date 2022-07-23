package com.happyworldgames.carclimatcontroll

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.happyworldgames.carclimatcontroll.adapter.MainRecyclerViewAdapter
import com.happyworldgames.carclimatcontroll.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private val activityMainBinding by lazy { ActivityMainBinding.inflate(layoutInflater) }
    private val mainAdapter by lazy { MainRecyclerViewAdapter() }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(activityMainBinding.root)

        activityMainBinding.mainRecyclerView.layoutManager = LinearLayoutManager(this)
        activityMainBinding.mainRecyclerView.adapter = mainAdapter
    }
}