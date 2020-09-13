import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';

class CategorySelector extends StatefulWidget {
  @override
  _CategorySelectorState createState() => _CategorySelectorState();
}

class _CategorySelectorState extends State<CategorySelector> {
  int _selectedIndex = 0;
  final List<String> _categoriesList = [
    'Messages',
    'Online',
    'Groups',
    'Requests'
  ];

  @override
  Widget build(BuildContext context) {
    return Container(
      height: 90,
      color: Theme.of(context).primaryColor,
      child: _categoriesWidget(),
    );
  }

  //##################################################
  // WIDGET BUILDERS
  //##################################################

  ListView _categoriesWidget() {
    return ListView.builder(
      itemCount: _categoriesList.length,
      itemBuilder: _categoryItemBuilder,
      scrollDirection: Axis.horizontal,
    );
  }

  Widget _categoryItemBuilder(BuildContext context, int index) {
    return GestureDetector(
      child: _categoryItemText(context, index),
      onTap: () => _onCategoryTapped(index),
    );
  }

  Widget _categoryItemText(BuildContext context, int index) {
    return Padding(
      padding: EdgeInsets.symmetric(
        horizontal: 20.0,
        vertical: 30.0,
      ),
      child: Text(
        _categoriesList[index],
        style: TextStyle(
          color: (index == _selectedIndex) ? Colors.white : Colors.white60,
          fontSize: 24.0,
          fontWeight: FontWeight.bold,
          letterSpacing: 1.2,
        ),
      ),
    );
  }

  //##################################################
  // UTILITY FUNCTIONS
  //##################################################

  void _onCategoryTapped(int index) {
    setState(() {
      _selectedIndex = index;
    });
  }
}
