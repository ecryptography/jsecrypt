# JsEcrypt

[![npm][npm-badge]][npm]
[![JsEcrypt][github-ci-badge]][github-ci]
[![License][license-badge]][license]

_Node.js_ wrapper for [Ecrypt crypto library](https://github.com/cossacklabs/ecrypt).

Ecrypt is a convenient cryptographic library for data protection. 
It provides secure messaging with forward secrecy and secure data storage. Ecrypt is aimed at modern development practices and has a unified API across 12 platforms, including Node.js, WebAssembly, Python, iOS/macOS, and Java/Android.

By [Cossack Labs](https://www.cossacklabs.com/ecrypt/).

[npm]: https://www.npmjs.com/package/jsecrypt
[npm-badge]: https://img.shields.io/npm/v/jsecrypt.svg
[github-ci]: https://github.com/cossacklabs/ecrypt/actions?query=workflow%3AJsEcrypt
[github-ci-badge]: https://github.com/cossacklabs/ecrypt/workflows/JsEcrypt/badge.svg
[license]: LICENSE
[license-badge]: https://img.shields.io/npm/l/jsecrypt.svg

## Getting started

### Installation

JsEcrypt requires native Ecrypt library to be installed.
Please refer to the [installation instructions](https://docs.cossacklabs.com/ecrypt/languages/nodejs/installation/).

After that install the latest version of JsEcrypt:

```
npm install jsecrypt
```

Import it into your project:

```javascript
const ecrypt = require('jsecrypt')
```

That's it!

### Documentation

Read the following resources to learn more:

  - [How to use JsEcrypt with JavaScript](https://docs.cossacklabs.com/ecrypt/languages/nodejs/).
  - [General documentation for Ecrypt library on Cossack Labs Documentation Server](https://docs.cossacklabs.com/ecrypt/).

### Additional resources  
  - If WebAssembly would be a better match for your project, see [WasmEcrypt wrapper](https://www.npmjs.com/package/wasm-ecrypt).

## Licensing

JsEcrypt is distributed under [Apache 2.0 license](https://www.apache.org/licenses/LICENSE-2.0).
