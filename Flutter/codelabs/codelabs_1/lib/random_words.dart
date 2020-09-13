import 'package:flutter/material.dart';
import 'package:english_words/english_words.dart';

class RandomWords extends StatefulWidget {
  @override
  _RandomWordsState createState() => _RandomWordsState();
}

class _RandomWordsState extends State<RandomWords> {
  List<WordPair> _suggestions = <WordPair>[];
  Set<WordPair> _saved = Set<WordPair>();
  TextStyle _biggerFont = const TextStyle(fontSize: 18);

  @override
  Widget build(BuildContext context) {
    return _buildSuggestions();
  }

  Widget _buildSuggestions() {
    return ListView.builder(
      padding: EdgeInsets.all(16),
      itemBuilder: (BuildContext context, int i) {
        if (i.isOdd) {
          return Divider();
        }

        final int index = i ~/ 2;
        if (index >= _suggestions.length) {
          _suggestions.addAll(generateWordPairs().take(10));
        }
        return _buildRow(_suggestions[index]);
      },
    );
  }

  Widget _buildRow(WordPair pair) {
    bool alreadySaved = _saved.contains(pair);
    return ListTile(
      title: Text(
        pair.asPascalCase,
        style: _biggerFont,
      ),
      trailing: Icon(
        alreadySaved ? Icons.favorite : Icons.favorite_border,
        color: alreadySaved ? Colors.red : null,
      ),
      onTap: () {
        setState(() {
          if(alreadySaved) {
            _saved.remove(pair);
          } else {
            _saved.add(pair);
          }
        });
      },
    );
  }
}
