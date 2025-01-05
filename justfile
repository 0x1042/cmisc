target := "buildDir"

build:
  meson setup --buildtype release -Db_lto=true -Db_lto_mode=thin -Db_pie=true {{target}}
  meson compile -C {{target}} --verbose
  ln -sf buildDir/compile_commands.json .

asan:
  meson setup {{target}} -Db_sanitize=address -Db_lundef=false
  meson compile -C {{target}} --verbose
  ln -sf buildDir/compile_commands.json .

run_test:
    ./buildDir/unittest/xmacro_test.c.bin --verbose --full-stats

clean:
    meson compile --clean -C {{target}}

test:
    meson test -C {{target}} -v

scan:
    meson setup {{target}}
    ninja -C builddir scan-build
