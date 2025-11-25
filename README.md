# cube

## Building

```bash
$ cmake --workflow --preset release
```

You can use the `debug` preset to make a debug build.

## Code formatting

Automatic source code formatting is done using clang-format and pre-commit.

Install pre-commit using pip:
```bash
$ pip install pre-commit
```

Install the git hook script to run clang-format on every commit:
```bash
$ pre-commit install
```

## License

cube is released under the [MIT License](LICENSE).
