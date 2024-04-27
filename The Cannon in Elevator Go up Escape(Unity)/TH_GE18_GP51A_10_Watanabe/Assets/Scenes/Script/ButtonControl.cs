using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class ButtonControl : MonoBehaviour
{
    int selectNun = 0;
    int selectMax = 1;
    bool openButtonHit = false;
    bool closeButtonHit = false;
    ButtonHit openButtonHitScript;
    ButtonHit exitButtonHitScript;
    AudioSource audioSource;

    public GameObject startButton;
    public GameObject endButton;
    public GameObject titleCanvas;
    public AudioClip switchOn;

    // Start is called before the first frame update
    void Start()
    {
        selectNun = 0;
        openButtonHitScript = startButton.GetComponent<ButtonHit>();
        exitButtonHitScript = endButton.GetComponent<ButtonHit>();
        audioSource = GetComponent<AudioSource>();
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.RightArrow) || Input.GetKeyDown(KeyCode.D) && selectNun > 0)
        {
            audioSource.pitch = 1.5f;//ピッチを変更
            audioSource.PlayOneShot(switchOn);
            selectNun--;
        }

        if (Input.GetKeyDown(KeyCode.LeftArrow) || Input.GetKeyDown(KeyCode.A) && selectNun < selectMax)
        {
            audioSource.pitch = 1.5f;//ピッチを変更
            audioSource.PlayOneShot(switchOn);
            selectNun++;
        }

        switch (selectNun)
        {
            case 0:
                StartCoroutine(StartButtonCoroutine());
                break;
            case 1:
                StartCoroutine(EndButtonCoroutine());
                break;
            default:
                break;
        }
    }

    //ゲームスタートボタン
    IEnumerator StartButtonCoroutine()
    {
        //選択中の処理
        exitButtonHitScript.ButtonNoLite();
        openButtonHitScript.ButtonLite();

        //押したときの処理
        if (Input.GetKey(KeyCode.Return) || Input.GetKey(KeyCode.E) && openButtonHit == false)
        {
            openButtonHit = true;
            audioSource.pitch = 1.0f;//ピッチを戻す
            audioSource.PlayOneShot(switchOn);
            yield return new WaitForSeconds(0.5f);

            titleCanvas.gameObject.SetActive(false);
            LightControl.instance.lightCenterFun(false);//電気を消す
            LightControl.instance.lightRightFun(false);
            SceneManager.LoadScene("ElevatorScene");//エレベーターシーンに移行
        }
    }

    //ゲーム終了ボタン
    IEnumerator EndButtonCoroutine()
    {
        //選択中の処理
        openButtonHitScript.ButtonNoLite();
        exitButtonHitScript.ButtonLite();

        //押したときの処理
        if (Input.GetKey(KeyCode.Return) || Input.GetKey(KeyCode.E) && closeButtonHit == false)
        {
            closeButtonHit = true;
            audioSource.pitch = 1.0f;//ピッチを戻す
            audioSource.PlayOneShot(switchOn);
            yield return new WaitForSeconds(0.5f);

            titleCanvas.gameObject.SetActive(false);
            LightControl.instance.lightCenterFun(false);//電気を消す
            LightControl.instance.lightRightFun(false);
            LightControl.instance.lightLeftFun(false);
            yield return new WaitForSeconds(0.5f);

#if UNITY_EDITOR //UnityEditorでの実行なら
            //再生モードを解除する
            UnityEditor.EditorApplication.isPlaying = false;
#else //UnityEditorでの実行でなければ(→ビルド後)なら
              //アプリケーションを終了する
              Application.Quit();
#endif
        }
    }
}
