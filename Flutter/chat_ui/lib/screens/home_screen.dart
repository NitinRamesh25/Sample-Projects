import 'package:chat_ui/widgets/chats_container.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';

import 'package:chat_ui/widgets/category_selector.dart';

class HomeScreen extends StatefulWidget {
  @override
  _HomeScreenState createState() => _HomeScreenState();
}

class _HomeScreenState extends State<HomeScreen> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Theme.of(context).primaryColor,
      appBar: AppBar(
        centerTitle: true,
        elevation: 0,
        leading: _menuButton(),
        title: _title(),
        actions: _actionButtons(),
      ),
      body: _body(),
    );
  }

  //##################################################
  // WIDGET BUILDERS - APP_BAR
  //##################################################

  IconButton _menuButton() {
    return IconButton(
      icon: Icon(Icons.menu),
      iconSize: 30,
      color: Colors.white,
      onPressed: () {},
    );
  }

  Text _title() {
    return Text(
      "Chats",
      style: TextStyle(
        fontSize: 28,
        fontWeight: FontWeight.bold,
      ),
    );
  }

  List<Widget> _actionButtons() {
    return <Widget>[
      IconButton(
        icon: Icon(Icons.search),
        iconSize: 30,
        color: Colors.white,
        onPressed: () {},
      ),
    ];
  }

  //##################################################
  // WIDGET BUILDERS - BODY
  //##################################################

  Column _body() {
    return Column(
      children: <Widget>[
        CategorySelector(),
        ChatsContainer(),
      ],
    );
  }
}
