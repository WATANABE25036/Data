using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CreateBullet : MonoBehaviour
{
    GameObject muzzle;
    AudioSource audioSource;
    bool shotKeyFg = false;
    float startTime;

    public KeyCode shotKey = KeyCode.Space; //発射キー
    public GameObject prefabObj; //弾のプレハブ
    public float shotPower = 15.0f; //弾の発射速度
    public AudioClip shotSound;

    void Start()
    {
        muzzle = transform.Find("Muzzle").gameObject;
        audioSource = GetComponent<AudioSource>();
    }

    void Update()
    {
        if (Input.GetKey(shotKey)) //ショットキーが押されたら
        {
            if (shotKeyFg == false)
            {
                shotKeyFg = true;

                //発射音
                audioSource.pitch = 1.0f + Random.Range(0.0f, 0.5f);
                audioSource.PlayOneShot(shotSound);

                //カメラシェイク
                if (CameraShake.shake == false)
                {
                    CameraShake.shake = true;
                    StartCoroutine("Coroutine");
                }

                //弾を出現させる地点
                Vector3 vec = muzzle.transform.position + muzzle.transform.forward * 0.2f; //キャラクターの位置より少し前
                vec.y += 0.0f; //上方向に少しずらす

                //弾のオブジェクトを生成
                GameObject obj = Instantiate(prefabObj, vec, Quaternion.identity); //vecの位置にprefabObjを出現させる

                //カメラの前方へむかってAddForceする
                obj.GetComponent<Rigidbody>().AddForce(muzzle.transform.forward * shotPower, ForceMode.Impulse);

            }
        }
        else
        {
            shotKeyFg = false;
        }
    }

    private IEnumerator Coroutine()
    {
        yield return new WaitForSeconds(0.3f);
        CameraShake.shake = false;
        yield break;//コルーチンを終了
    }
}
