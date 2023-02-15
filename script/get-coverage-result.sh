#set -e

Build() {
  echo "########################"
  echo "Build Project..."

  mkdir -p ./build
  cd build
  cmake ..
  make
  cd ..
}

Test() {
  echo "########################"
  echo "Run test..."
  cd build
  test/ChatClientTest.exe
  cd ..
}

Coverage() {
  echo "########################"
  echo "Create gcov result..."
  mkdir -p ./coverage-result
  gcovr --html -o index.html --html-details
  mv *.html coverage-result

  echo "########################"
  echo "Finish! Please check coverage-result/index.html"
}

USE_BUILD=${1}

rm -rf ./coverage-result

if [ -z ${USE_BUILD} ]; then
  Test
  Coverage
else
  Build
  Test
  Coverage
fi