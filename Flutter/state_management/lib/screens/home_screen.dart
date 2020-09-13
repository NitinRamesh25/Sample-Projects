import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:state_management/block/counter_block.dart';
import 'package:state_management/widgets/increment.dart';

class HomeScreen extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    // searches up with widget tree to check for providers
    final CounterBlock counterBlock = Provider.of<CounterBlock>(context);

    return Scaffold(
      appBar: AppBar(
        title: Center(
          child: Text("home screen"),
        ),
      ),
      body: Column(
        children: <Widget>[
          Center(
            child: Text(counterBlock.counter.toString()),
          ),
          IncrementButton(),
        ],
      ),
    );
  }
}
