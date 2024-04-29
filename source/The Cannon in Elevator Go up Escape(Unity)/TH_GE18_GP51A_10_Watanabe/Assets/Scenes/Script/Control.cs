using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Control : MonoBehaviour
{
    float startTimeR;
    float startTimeEsc;

    public GameObject canvas;

    // Start is called before the first frame update
    void Start()
    {
        DontDestroyOnLoad(this);//次のシーンでも引き継ぐ
    }

    // Update is called once per frame
    void Update()
    {
        R();
        ESC();
        //ControlActive();
    }

    void R()
    {
        //Rを長押ししたら
        if (Input.GetKeyDown(KeyCode.R))
        {
            startTimeR = Time.time;
        }

        if (!Input.GetKey(KeyCode.R))
        {
            startTimeR = Time.time;
        }

        if (Input.GetKey(KeyCode.R) && startTimeR + 3 < Time.time && SceneManager.GetActiveScene().name != "TitleScene")
        {
            SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);//今のシーンを再読み込み
        }
    }

    void ESC()
    {
        //ESCを長押ししたら
        if (Input.GetKeyDown(KeyCode.Escape))
        {
            startTimeEsc = Time.time;
        }

        if (!Input.GetKey(KeyCode.Escape))
        {
            startTimeEsc = Time.time;
        }

        if (Input.GetKey(KeyCode.Escape) && startTimeEsc + 3 < Time.time && SceneManager.GetActiveScene().name != "TitleScene")
        {
            Destroy(GameObject.Find("Elevator"));//エレベーターを削除
            Destroy(GameObject.Find("Cannon"));//キャノンを削除
            Destroy(GameObject.Find("Control"));//コントロールを削除
            SceneManager.LoadScene("TitleScene");//タイトルシーンを読み込み
        }
    }

    void ControlActive()
    {
        //操作説明表示
        if (Input.GetKeyDown(KeyCode.Tab) && canvas.gameObject.activeSelf == false)
        {
            canvas.gameObject.SetActive(true);
        }
        else if (Input.GetKeyDown(KeyCode.Tab) && canvas.gameObject.activeSelf == true)
        {
            canvas.gameObject.SetActive(false);
        }
    }
}
