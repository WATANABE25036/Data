using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StartControl : MonoBehaviour
{
    public GameObject titleCanvas;

    IEnumerator Start()
    {
        Cursor.visible = false;//カーソルを消す
        yield return new WaitForSeconds(0.0f);//これを入れないと下記が実行されない

        LightControl.instance.lightCenterSilentFun(false);
        LightControl.instance.lightRightSilentFun(false);
        LightControl.instance.lightLeftSilentFun(false);
        yield return new WaitForSeconds(2.0f);

        titleCanvas.gameObject.SetActive(true);
        LightControl.instance.lightRightFun(true);
        yield return new WaitForSeconds(2.5f);

        LightControl.instance.lightCenterFun(true);

        yield break;//コルーチンを終了
    }

    // Update is called once per frame
    void Update()
    {

    }
}
