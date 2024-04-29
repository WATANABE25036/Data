using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class FloorCunLamp : MonoBehaviour
{
    public string shineName;

    public Material ndirectLighting;           // 割り当てるマテリアル
    public Material ndirectNoLighting;           // 割り当てるマテリアル

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        //指定した階であれば点灯
        var currentScreen = SceneManager.GetActiveScene();

        if (currentScreen.name == shineName)
        {
            this.GetComponent<Renderer>().material = ndirectLighting;
        }

        //違う階であれば消灯
        if (currentScreen.name != shineName && currentScreen.name != "MoveElevator" && currentScreen.name != "TitleScene" && currentScreen.name != "ElevatorScene")
        {
            this.GetComponent<Renderer>().material = ndirectNoLighting;
        }
    }
}
