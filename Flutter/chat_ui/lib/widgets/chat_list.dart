import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';

import 'package:chat_ui/models/message_model.dart';
import 'package:chat_ui/screens/chat_screen.dart';

class ChatList extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Expanded(
      child: Container(
        decoration: _chatContainerDecoration(),
        child: _chatList(),
      ),
    );
  }

  BoxDecoration _chatContainerDecoration() {
    return BoxDecoration(
      color: Colors.white,
      borderRadius: BorderRadius.only(
        topLeft: Radius.circular(30.0),
        topRight: Radius.circular(30.0),
      ),
    );
  }

  //##################################################
  // WIDGET BUILDERS - BODY
  //##################################################

  Widget _chatList() {
    return ClipRRect(
      borderRadius: BorderRadius.only(
        topLeft: Radius.circular(30.0),
        topRight: Radius.circular(30.0),
      ),
      child: ListView.builder(
        itemCount: chats.length,
        itemBuilder: _chatBuilder,
      ),
    );
  }

  Widget _chatBuilder(BuildContext context, int index) {
    final Message chat = chats[index];
    return GestureDetector(
      onTap: () => Navigator.push(
        context,
        MaterialPageRoute(
          builder: (_) => ChatScreen(user: chat.sender),
        ),
      ),
      child: Container(
        margin: EdgeInsets.all(5.0),
        padding: EdgeInsets.symmetric(horizontal: 20.0, vertical: 10.0),
        decoration: BoxDecoration(
            color: chat.unread ? Color(0xFFFFEFEE) : Colors.white,
            borderRadius: BorderRadius.only(
              topRight: Radius.circular(20.0),
              bottomRight: Radius.circular(20.0),
            )),
        child: Row(
          mainAxisAlignment: MainAxisAlignment.spaceBetween,
          children: <Widget>[
            Row(
              children: <Widget>[
                CircleAvatar(
                  radius: 35.0,
                  backgroundImage: AssetImage(chat.sender.imageUrl),
                ),
                SizedBox(
                  width: 10,
                ),
                Column(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: <Widget>[
                    Text(
                      chat.sender.name,
                      style: TextStyle(
                        color: Colors.grey,
                        fontSize: 15.0,
                        fontWeight: FontWeight.bold,
                      ),
                    ),
                    SizedBox(
                      height: 5,
                    ),
                    Container(
                      width: MediaQuery.of(context).size.width * 0.45,
                      child: Text(
                        chat.text,
                        style: TextStyle(
                          color: Colors.blueGrey,
                          fontSize: 15.0,
                          fontWeight: FontWeight.w600,
                        ),
                        overflow: TextOverflow.ellipsis,
                      ),
                    ),
                  ],
                ),
              ],
            ),
            Column(
              children: <Widget>[
                Text(
                  chat.time,
                  style: TextStyle(
                    color: Colors.grey,
                    fontSize: 15.0,
                    fontWeight: FontWeight.bold,
                  ),
                ),
                SizedBox(height: 10.0),
                chat.unread
                    ? Container(
                        width: 40.0,
                        height: 20.0,
                        decoration: BoxDecoration(
                          borderRadius: BorderRadius.circular(30.0),
                          color: Theme.of(context).primaryColor,
                        ),
                        alignment: Alignment.center,
                        child: Text(
                          'NEW',
                          style: TextStyle(
                            color: Colors.white,
                            fontSize: 12.0,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                      )
                    : Text('')
              ],
            ),
          ],
        ),
      ),
    );
  }
}
