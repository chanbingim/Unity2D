using UnityEngine.UIElements;

namespace Client_Structs
{
    public struct LOGIN_INFO
    {
        public LOGIN_INFO(string userid, string pw, string uid, string email)
        {
            user_id = userid;
            Password = pw;
            UID = uid;
            Email = email;
        }

        public string user_id;
        public string Password;
        public string UID;
        public string Email;
    }
}
