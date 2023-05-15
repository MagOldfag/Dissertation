using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using RootMotion.FinalIK;

public class SimpleController : MonoBehaviour
{
    public Transform[] servos;
    public int[] delta;
    public int[] multiply;
    public int[] lastAngle;
    SerialController serialController;
    // Start is called before the first frame update
    void Start()
    {
        serialController = GameObject.FindObjectOfType<SerialController>();
        lastAngle = new int[servos.Length];
    }

    float Clamp(float angle) {
        if (angle > 180) {
            angle -= 360;
        }
        if (angle < -180) {
            angle += 360;
        }
        return angle;
    }
    int i = 0;
    float lastSendTime = 0;

    // Update is called once per frame
    void Update()
    {
        if (Time.time < lastSendTime+0.5f) {
            return;
        }
        
        string a = "(";
        
        a += 40 + ",";       // Клешня

        for (int i = 0; i < servos.Length; i++) {
            var servo = servos[i];
            var limit = servo.transform.GetComponent<RotationLimitHinge>();
            int angle = Mathf.RoundToInt(Clamp(Vector3.Dot(servo.localEulerAngles, limit.axis) * multiply[i]) + delta[i]);
            
            lastAngle[i] = angle;
            a += angle;
            if (i != servos.Length-1) {
                a += ",";
            }
        }
        a += ")";
        Debug.Log(a);
        serialController.SendSerialMessage(a);    

        lastSendTime = Time.time;
    }
}
