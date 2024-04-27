using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LastControl : MonoBehaviour
{
    float time;
    bool updateLight = false ;

    // Start is called before the first frame update
    void Start()
    {
        LightControl.instance.lightCenterFun(false);
        LightControl.instance.lightRightFun(false);
        LightControl.instance.lightLeftFun(false);
    }

    // Update is called once per frame
    void Update()
    {
        time += Time.deltaTime;

        if (time > 3 && updateLight == false)
        {
            LightControl.instance.lightCenterFun(true);
            LightControl.instance.lightRightFun(true);
            LightControl.instance.lightLeftFun(true);
            updateLight = true;
        }
    }
}
