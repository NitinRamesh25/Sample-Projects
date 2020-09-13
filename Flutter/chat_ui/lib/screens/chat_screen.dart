import 'package:chat_ui/models/message_model.dart';
import 'package:chat_ui/models/user_model.dart';

import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';

class ChatScreen extends StatefulWidget {
  final User user;

  ChatScreen({this.user});

  @override
  _ChatScreenState createState() => _ChatScreenState();
}

class _ChatScreenState extends State<ChatScreen> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Theme.of(context).primaryColor,
      appBar: _appBar(),
      body: _body(),
    );
  }

  //##################################################
  // WIDGET BUILDERS - APP BAR
  //##################################################

  Widget _appBar() {
    return AppBar(
      title: Text(widget.user.name),
      centerTitle: true,
      actions: _actionButtons(),
      elevation: 0.0,
    );
  }

  List<Widget> _actionButtons() {
    return <Widget>[
      IconButton(
        icon: Icon(Icons.more_horiz),
        iconSize: 30,
        color: Colors.white,
        onPressed: () {},
      ),
    ];
  }

  //##################################################
  // WIDGET BUILDERS - BODY
  //##################################################

  Widget _body() {
    return GestureDetector(
      onTap: () => FocusScope.of(context).unfocus(),
      child: Column(
        children: <Widget>[
          Expanded(
            child: Container(
              decoration: BoxDecoration(
                color: Colors.white,
                borderRadius: BorderRadius.only(
                  topLeft: Radius.circular(30.0),
                  topRight: Radius.circular(30.0),
                ),
              ),
              child: ClipRRect(
                borderRadius: BorderRadius.only(
                  topLeft: Radius.circular(30.0),
                  topRight: Radius.circular(30.0),
                ),
                child: ListView.builder(
                  reverse: true,
                  padding: EdgeInsets.only(top: 15.0),
                  itemCount: messages.length,
                  itemBuilder: (BuildContext context, int index) {
                    final Message message = messages[index];
                    bool isMe = (message.sender.id == currentUser.id);
                    return _buildMessage(message, isMe);
                  },
                ),
              ),
            ),
          ),
          _buildMessageComposer(),
        ],
      ),
    );
  }

  Widget _buildMessage(Message message, bool isMe) {
    return Container(
      margin: isMe
          ? EdgeInsets.only(top: 8.0, bottom: 8.0, left: 80.0)
          : EdgeInsets.only(top: 8.0, bottom: 8.0, right: 80.0),
      padding: EdgeInsets.symmetric(
        horizontal: 25.0,
        vertical: 15.0,
      ),
      decoration: BoxDecoration(
        color: isMe ? Theme.of(context).accentColor : Color(0XFFFFEFEE),
        borderRadius: isMe
            ? BorderRadius.only(
                topLeft: Radius.circular(20.0),
                bottomLeft: Radius.circular(20.0),
              )
            : BorderRadius.only(
                topRight: Radius.circular(20.0),
                bottomRight: Radius.circular(20.0),
              ),
      ),
      child: Column(
        crossAxisAlignment:
            isMe ? CrossAxisAlignment.end : CrossAxisAlignment.start,
        children: <Widget>[
          Text(message.time),
          SizedBox(
            height: 5.0,
          ),
          Text(message.text),
        ],
      ),
    );
  }

  Widget _buildMessageComposer() {
    return Container(
      padding: EdgeInsets.symmetric(horizontal: 8.0),
      height: 70.0,
      color: Colors.white,
      child: Row(
        children: <Widget>[
          IconButton(
            icon: Icon(Icons.photo),
            iconSize: 25.0,
            color: Theme.of(context).primaryColor,
            onPressed: () {},
          ),
          Expanded(
            child: TextField(
              textCapitalization: TextCapitalization.sentences,
              onChanged: (value) {},
              decoration: InputDecoration.collapsed(
                hintText: 'Enter your message',
              ),
            ),
          ),
          IconButton(
            icon: Icon(Icons.send),
            iconSize: 25.0,
            color: Theme.of(context).primaryColor,
            onPressed: () {},
          ),
        ],
      ),
    );
  }
}
