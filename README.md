# cube

## Building

On Unix-like systems, you will need a few extra packages for compiling GLFW: [Installing dependencies](https://www.glfw.org/docs/latest/compile_guide.html#compile_deps).

```bash
$ cmake --workflow --preset release
```

You can use the `debug` preset to make a debug build. If Ninja and Clang are not available, use `default-release` or the `default-debug` preset.

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
