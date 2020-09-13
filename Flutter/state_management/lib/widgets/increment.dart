import 'package:flutter/material.dart';
import 'package:state_management/block/counter_block.dart';
import 'package:provider/provider.dart';

class IncrementButton extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    final CounterBlock counterBlock = Provider.of<CounterBlock>(context);

    return FlatButton.icon(
      onPressed: counterBlock.increment,
      icon: Icon(Icons.add),
      label: Text("Add"),
    );
  }
}
