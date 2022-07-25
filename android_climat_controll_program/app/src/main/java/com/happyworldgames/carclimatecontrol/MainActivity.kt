package com.happyworldgames.carclimatecontrol

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import androidx.recyclerview.widget.LinearLayoutManager
import com.happyworldgames.carclimatecontrol.databinding.ActivityMainBinding
import com.happyworldgames.carclimatecontrol.adapter.MainRecyclerViewAdapter

class MainActivity : AppCompatActivity() {
    private val serviceViewItemList: ArrayList<MainRecyclerViewAdapter.ViewItem> = arrayListOf(
        // Fan
        MainRecyclerViewAdapter.ViewItem(R.layout.text_view_holder, getString(R.string.fan)),

        // Temp Servo

        // Way Servo, not work now

        // Temp Sensor

        // Other

    )

    private val activityMainBinding by lazy { ActivityMainBinding.inflate(layoutInflater) }
    private val mainAdapter by lazy { MainRecyclerViewAdapter() }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(activityMainBinding.root)

        /*
            Loading screen
            send request
            receive data
            set view item list
         */
        mainAdapter.setViewList(serviceViewItemList)
        activityMainBinding.mainRecyclerView.layoutManager = LinearLayoutManager(this)
        activityMainBinding.mainRecyclerView.adapter = mainAdapter
    }
}