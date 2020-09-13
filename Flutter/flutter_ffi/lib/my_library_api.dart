// Copyright (c) 2019, the Dart project authors.  Please see the AUTHORS file
// for details. All rights reserved. Use of this source code is governed by a
// BSD-style license that can be found in the LICENSE file.

import 'dart:ffi';
import 'dart:io';

class MyLibraryAPI {
  static final MyLibraryAPI _myLibraryAPI = MyLibraryAPI._internal();

  factory MyLibraryAPI() {
    return _myLibraryAPI;
  }

  MyLibraryAPI._internal();

  int favouriteNumber() {
    final dylib = DynamicLibrary.open(_libPath());

    final int Function() favNumber = dylib
        .lookup<NativeFunction<Int32 Function()>>('favouriteNumber')
        .asFunction();

    return favNumber();
  }

  String _libPath() {
    if (Platform.isWindows) return r'my_library.dll';
    if (Platform.isMacOS) return 'libmy_library.dylib';

    return 'libmy_library.so';
  }
}
