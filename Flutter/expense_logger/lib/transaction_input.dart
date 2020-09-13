import "package:flutter/material.dart";

import "./transaction_data.dart";

class TransactionInput extends StatelessWidget {
  final Function inputAccepted;
  final titleController = TextEditingController();
  final amountController = TextEditingController();

  TransactionInput(this.inputAccepted);

  Widget build(BuildContext context) {
    return Card(
      child: Container(
        padding: EdgeInsets.all(5),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.end,
          children: <Widget>[
            TextField(
              decoration: InputDecoration(
                labelText: "Title",
              ),
              controller: this.titleController,
            ),
            TextField(
              decoration: InputDecoration(
                labelText: "Amount",
              ),
              controller: this.amountController,
            ),
            FlatButton(
              onPressed: () {
                inputAccepted(TransactionData(
                    id: "NA",
                    title: this.titleController.text,
                    amount: double.parse(this.amountController.text),
                    dateTime: DateTime.now(),));
              },
              child: Text(
                "Add Transaction",
                style: TextStyle(
                  color: Colors.purple,
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }
}
