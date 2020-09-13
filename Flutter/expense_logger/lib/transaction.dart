import "package:flutter/material.dart";
import "package:intl/intl.dart";

import "./transaction_data.dart";
import "./transaction_input.dart";

class _Price extends StatelessWidget {
  final double amount;

  _Price(this.amount);

  Widget build(BuildContext context) {
    return Container(
      margin: EdgeInsets.all(15),
      padding: EdgeInsets.all(10),
      decoration: BoxDecoration(
        border: Border.all(
          width: 2,
          color: Colors.purple,
        ),
        borderRadius: BorderRadius.all(Radius.circular(5)),
      ),
      child: Text(
        "Rs ${amount.toString()}",
        style: TextStyle(
          fontWeight: FontWeight.bold,
          fontSize: 20,
          color: Colors.purple,
        ),
      ),
    );
  }
}

class _TransactionDetails extends StatelessWidget {
  final String title;
  final DateTime dateTime;

  _TransactionDetails(this.title, this.dateTime);

  Widget build(BuildContext context) {
    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: <Widget>[
        Text(
          this.title,
          style: TextStyle(
            fontSize: 16,
            fontWeight: FontWeight.bold,
          ),
        ),
        Text(
          DateFormat.yMMMd().format(this.dateTime),
          style: TextStyle(
            color: Colors.grey,
          ),
        ),
      ],
    );
  }
}

class Transaction extends StatefulWidget {
  State<Transaction> createState() {
    return _TransactionState();
  }
}

class _TransactionState extends State<Transaction> {
  List<TransactionData> transactions = [
    TransactionData(
      id: "A001",
      title: "UPI Swiggy",
      amount: 230,
      dateTime: DateTime.now(),
    ),
    TransactionData(
      id: "A002",
      title: "Groceries",
      amount: 450.50,
      dateTime: DateTime.now(),
    ),
  ];

  void _addTransaction(TransactionData data) {
    setState(() {
      transactions.add(data);
    });
  }

  Widget build(BuildContext context) {
    return Column(
      children: [
        TransactionInput(_addTransaction),
        Container(
          height: 320,
          // ListView.builder creates widgets that are only visible,
          // which makes the app faster for long lists
          child: ListView.builder(
            itemCount: transactions.length,
            itemBuilder: (context, index) {
              return Card(
                child: Row(
                  children: <Widget>[
                    _Price(transactions[index].amount),
                    _TransactionDetails(
                      transactions[index].title,
                      transactions[index].dateTime,
                    ),
                  ],
                ),
              );
            },
          ),
        ),
      ],
    );
  }
}
