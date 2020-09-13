import 'package:chat_ui/screens/chat_screen.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';

import 'package:chat_ui/models/message_model.dart';

class FavouriteContacts extends StatelessWidget {
  Widget build(BuildContext context) {
    return Padding(
      padding: EdgeInsets.symmetric(vertical: 10.0),
      child: Column(
        children: <Widget>[
          _favouriteContactHeader(),
          _favouriteContacts(),
        ],
      ),
    );
  }

  //##################################################
  // WIDGET BUILDERS
  //##################################################

  Widget _favouriteContactHeader() {
    return Padding(
      padding: const EdgeInsets.symmetric(horizontal: 20.0),
      child: Row(
        mainAxisAlignment: MainAxisAlignment.spaceBetween,
        children: <Widget>[
          Text(
            "Favourite Contacts",
            style: TextStyle(
              color: Colors.blueGrey,
              fontSize: 18.0,
              fontWeight: FontWeight.bold,
              letterSpacing: 1.0,
            ),
          ),
          IconButton(
            icon: Icon(Icons.more_horiz),
            iconSize: 30.0,
            color: Colors.blueGrey,
            onPressed: () {},
          )
        ],
      ),
    );
  }

  Widget _favouriteContacts() {
    return Container(
      height: 120.0,
      child: ListView.builder(
        padding: EdgeInsets.only(left: 10.0),
        scrollDirection: Axis.horizontal,
        itemCount: favourites.length,
        itemBuilder: _favouriteContactsItemBuilder,
      ),
    );
  }

  Widget _favouriteContactsItemBuilder(BuildContext context, index) {
    return GestureDetector(
      onTap: () => Navigator.push(
        context,
        MaterialPageRoute(
          builder: (_) => ChatScreen(user: favourites[index]),
        ),
      ),
      child: Padding(
        padding: EdgeInsets.all(10.0),
        child: Column(
          children: <Widget>[
            CircleAvatar(
              radius: 35.0,
              backgroundImage: AssetImage(favourites[index].imageUrl),
            ),
            SizedBox(
              height: 6.0,
            ),
            Text(
              favourites[index].name,
              style: TextStyle(
                color: Colors.blueGrey,
                fontSize: 16.0,
                fontWeight: FontWeight.w600,
              ),
            ),
          ],
        ),
      ),
    );
  }
}
