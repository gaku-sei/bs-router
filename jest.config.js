module.exports = {
  rootDir: "tests",
  testRegex: "\\/tests\\/.*_test(\\.bs)?\\.[jt]sx?$",
  transformIgnorePatterns: ["/node_modules/(?!bs-*|@glennsl).+\\.js$"]
};
