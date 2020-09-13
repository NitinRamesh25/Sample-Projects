import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';

import 'package:chat_ui/widgets/favourite_contacts.dart';
import 'package:chat_ui/widgets/chat_list.dart';

class ChatsContainer extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Expanded(
      child: Container(
        decoration: _chatsContainerDecoration(context),
        child: Column(
          children: <Widget>[
            FavouriteContacts(),
            ChatList(),
          ],
        ),
      ),
    );
  }

  BoxDecoration _chatsContainerDecoration(context) {
    return BoxDecoration(
      color: Theme.of(context).accentColor,
      borderRadius: BorderRadius.only(
        topLeft: Radius.circular(30.0),
        topRight: Radius.circular(30.0),
      ),
    );
  }
}
