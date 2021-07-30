[![Windows](https://github.com/FrancoisSestier/antity/actions/workflows/windows.yml/badge.svg)](https://github.com/FrancoisSestier/filesystem/actions/workflows/windows.yml) [![Ubuntu](https://github.com/FrancoisSestier/filesystem/actions/workflows/ubuntu.yml/badge.svg)](https://github.com/FrancoisSestier/filesystem/actions/workflows/ubuntu.yml) [![codecov](https://codecov.io/gh/FrancoisSestier/filesystem/branch/master/graph/badge.svg?token=ZPDP1TAO3Z)](https://codecov.io/gh/FrancoisSestier/filesystem) [![License: Unlicense](https://img.shields.io/badge/license-Unlicense-blue.svg)](http://unlicense.org/)

## filesystem
Open Source header only binary serializer writen on top of standard cpp library

## Goal
serialize vector, arrays, tuple fast, easily, and possibly asynchronously

## Supported data structure 
	vectors, arrays where the value_type is either trivially_copyable or has user defined fstream operators.
	tuple composed of serializable (has defined fstream operators) types


## Usage Design 

```c++
	
	struct trivial_struct {
		int a;
		char b;
		float c;
	}

	fs::filesystem filesystem;

    std::vector<trivial_struct> vec1
        = {{1, 'a', .1f}, {2, 'b', .2f}, {3, 'c', .3f}};

    filesystem.write("test2.bin", vec2);

    auto future = filesystem.read_async("test2.bin");

	auto vec2 = future.get(); // vec1 is the same as vec2 

```

## Examples 
see tests for more examples 
 
