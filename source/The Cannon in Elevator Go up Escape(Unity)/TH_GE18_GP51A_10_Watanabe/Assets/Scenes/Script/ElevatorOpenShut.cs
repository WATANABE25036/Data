using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class ElevatorOpenShut : MonoBehaviour
{
    GameObject doorRight, doorLeft;
    Vector3 targetPositionR, targetPositionL, firstPositionR, firstPositionL;
    private Vector3 velocityR = Vector3.zero;
    private Vector3 velocityL = Vector3.zero;
    bool openDoor = false;
    bool shutDoor = false;
    bool upHit = false;
    bool downHit = false;
    bool move = false;
    bool upDownDecision = false;
    bool hitTrigger = false;
    float startTime;
    int sceneNum;//今のシーン№
    float lastTime;
    float delayTime;
    public int fastStageScene = 3;
    public float targetX = 0;//目的座標
    public float smoothTime = 0.3F;//遷移時間
    public AudioSource elevatorAudioSource;
    public AudioSource elevatorOpenAudioSource;
    public AudioSource poonAudioSource;
    public AudioSource natureAudioSource;
    public AudioClip elevatorSound;
    public AudioClip elevatorOpenSound;
    public AudioClip poonSound;
    public AudioClip natureSound;
    public GameObject controlCanvasTips1;
    public GameObject controlCanvasTips2;

    public GameObject upLamp;
    public GameObject downLamp;
    public Material ndirectLighting;           // 割り当てるマテリアル
    public Material ndirectNoLighting;           // 割り当てるマテリアル

    // Start is called before the first frame update
    void Start()
    {
        SceneManager.LoadScene(fastStageScene);
        DontDestroyOnLoad(this);//次のシーンでも引き継ぐ
        doorRight = transform.Find("DoorRight").gameObject;
        doorLeft = transform.Find("DoorLeft").gameObject;
        targetPositionR = new Vector3(targetX, doorRight.transform.position.y, doorRight.transform.position.z);
        targetPositionL = new Vector3(-targetX, doorLeft.transform.position.y, doorLeft.transform.position.z);
        firstPositionR = new Vector3(doorRight.transform.position.x, doorRight.transform.position.y, doorRight.transform.position.z);
        firstPositionL = new Vector3(doorLeft.transform.position.x, doorLeft.transform.position.y, doorLeft.transform.position.z);

        StartCoroutine("Coroutine");
    }

    private IEnumerator Coroutine()
    {
        //ファーストステージの動き
        LightControl.instance.lightCenterFun(false);
        LightControl.instance.lightLeftFun(false);
        LightControl.instance.lightRightFun(false);
        yield return new WaitForSeconds(2.0f);

        if (SceneManager.GetActiveScene().name == "Stage1")//ステージ1以外では実行しない(デバッグ時実行しないようにするため)
        {
            controlCanvasTips1.gameObject.SetActive(true);
            LightControl.instance.lightLeftFun(true);
            yield return new WaitForSeconds(1.5f);
        }

        LightControl.instance.lightCenterFun(true);
        yield return new WaitForSeconds(1.5f);

        openDoor = true;//ドアを開ける
        yield break;//コルーチンを終了
    }

    // Update is called once per frame
    void Update()
    {
        upHit = UpButtonHit.upHit;
        downHit = DownButtonHit.downHit;

        if(hitTrigger == false)
        {
            StartCoroutine("CoroutineButtonHit");
        }

        if (openDoor == true)//ドアを開ける
        {
            //ラストステージの動き
            if (SceneManager.GetActiveScene().name == "LastStage")
            {
                lastTime += Time.deltaTime;

                if (lastTime > 5)
                {
                    if (doorRight.transform.position == firstPositionR && doorLeft.transform.position == firstPositionL)
                    {
                        //ランプ消灯
                        upLamp.GetComponent<Renderer>().material = ndirectNoLighting;
                        downLamp.GetComponent<Renderer>().material = ndirectNoLighting;
                        poonAudioSource.PlayOneShot(poonSound);//ポーンの音
                        elevatorOpenAudioSource.PlayOneShot(elevatorOpenSound);//ドアが開く音
                        natureAudioSource.PlayOneShot(natureSound);//自然音再生
                    }
                    doorRight.transform.position = Vector3.SmoothDamp(doorRight.transform.position, targetPositionR, ref velocityR, smoothTime);//(現在地, 目的地, ref 現在の速度, 遷移時間, 最高速度)
                    doorLeft.transform.position = Vector3.SmoothDamp(doorLeft.transform.position, targetPositionL, ref velocityL, smoothTime);
                }

                if (lastTime > 27)
                {
                    openDoor = false;
                    natureAudioSource.Stop();
                    Destroy(GameObject.Find("Elevator"));//エレベーターを削除
                    Destroy(GameObject.Find("Cannon"));//キャノンを削除
                    SceneManager.LoadScene("TitleScene");//タイトルシーンを読み込み
                }
            }

            //通常ステージの動き
            if (SceneManager.GetActiveScene().name != "LastStage")
            {
                if (doorRight.transform.position == firstPositionR && doorLeft.transform.position == firstPositionL)
                {
                    //ランプ消灯
                    upLamp.GetComponent<Renderer>().material = ndirectNoLighting;
                    downLamp.GetComponent<Renderer>().material = ndirectNoLighting;
                    poonAudioSource.PlayOneShot(poonSound);//ポーンの音
                    elevatorOpenAudioSource.PlayOneShot(elevatorOpenSound);//ドアが開く音
                }
                doorRight.transform.position = Vector3.SmoothDamp(doorRight.transform.position, targetPositionR, ref velocityR, smoothTime);//(現在地, 目的地, ref 現在の速度, 遷移時間, 最高速度)
                doorLeft.transform.position = Vector3.SmoothDamp(doorLeft.transform.position, targetPositionL, ref velocityL, smoothTime);

                if (doorRight.transform.position == targetPositionR && doorLeft.transform.position == targetPositionL || shutDoor == true)//ドアが完全に開いたら
                {
                    openDoor = false;
                }
            }
        }
        else if (shutDoor == true)//ドアを閉める
        {
            doorRight.transform.position = Vector3.SmoothDamp(doorRight.transform.position, firstPositionR, ref velocityR, 1.0f);//(現在地, 目的地, ref 現在の速度, 遷移時間, 最高速度)
            doorLeft.transform.position = Vector3.SmoothDamp(doorLeft.transform.position, firstPositionL, ref velocityL, 1.0f);

            if (doorRight.transform.position == firstPositionR && doorLeft.transform.position == firstPositionL)//ドアが完全に閉じたら
            {
                sceneNum = SceneManager.GetActiveScene().buildIndex;//今のシーン№を記録
                SceneManager.LoadScene("MoveElevator");//エレベーター移動シーンを読み込む
                move = true;
                startTime = Time.time;
                shutDoor = false;
            }
        }

        if (move == true)//エレベーター移動中に起こること
        {
            if (!elevatorAudioSource.isPlaying)//再生が終わってから再生する
            {
                elevatorAudioSource.PlayOneShot(elevatorSound);//駆動音
            }

            CameraShake.shake = true;//画面シェイク

            if (startTime + 2.5f < Time.time)
            {
                CameraShake.shake = false;//画面シェイク終了
                elevatorAudioSource.Stop();
            }

            if (startTime + 3.0f < Time.time)//待機時間
            {
                if (upDownDecision == true)
                {
                    SceneManager.LoadScene(sceneNum + 1); //次シーンを読み込む
                }
                else if (upDownDecision == false)
                {
                    SceneManager.LoadScene(sceneNum - 1); //前シーンを読み込む
                }
                hitTrigger = false;
                openDoor = true;
                move = false;
            }
        }

        //ステージ3になったら次の操作説明を出す
        if (SceneManager.GetActiveScene().name == "Stage3" && controlCanvasTips1.gameObject.activeSelf == true && controlCanvasTips2.gameObject.activeSelf == false)
        {
            controlCanvasTips1.gameObject.SetActive(false);
            controlCanvasTips2.gameObject.SetActive(true);

            LightControl.instance.lightRightFun(true);//点灯
            LightControl.instance.lightLeftSilentFun(false);//消灯
        }
        
        if(Input.GetKeyDown (KeyCode.Tab))
        {
            if(controlCanvasTips1.gameObject.activeSelf == true || controlCanvasTips2.gameObject.activeSelf == true)
            {
                controlCanvasTips1.gameObject.SetActive(false);
                controlCanvasTips2.gameObject.SetActive(false);
                LightControl.instance.lightRightFun(false);//消灯
                LightControl.instance.lightLeftSilentFun(false);//消灯
            }
            else if (controlCanvasTips1.gameObject.activeSelf == false || controlCanvasTips2.gameObject.activeSelf == false)
            {
                controlCanvasTips1.gameObject.SetActive(true);
                controlCanvasTips2.gameObject.SetActive(true);
                LightControl.instance.lightRightFun(true);//点灯
                LightControl.instance.lightLeftSilentFun(true);//点灯
            }
        }
    }

    private IEnumerator CoroutineButtonHit()
    {
        if ((upHit == true || downHit == true) && shutDoor == false)//アップもしくはダウンボタンを押したら
        {
            hitTrigger = true;

            if (upHit == true)
            {
                upLamp.GetComponent<Renderer>().material = ndirectLighting;//ランプ点灯
                upDownDecision = true;
            }
            else if (downHit == true)
            {
                downLamp.GetComponent<Renderer>().material = ndirectLighting;//ランプ点灯
                upDownDecision = false;
            }

            yield return new WaitForSeconds(1.5f);

            elevatorOpenAudioSource.PlayOneShot(elevatorOpenSound);//ドアが閉まる音

            shutDoor = true;
        }
    }
}
