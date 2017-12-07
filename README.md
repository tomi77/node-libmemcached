# libmemcached

## Table of contents

* [Requirements](#requirements)
* [Installation](#installation)
* [Usage](#usage)
* [API](#api)
  * [`get(key : String) : Buffer`](#getkey--string--buffer)

## Requirements

* `libmemcached`
* `libmemcached-dev`
* `gcc`

## Installation

~~~sh
npm i libmemcached
~~~

or

~~~sh
yarn add libmemcached
~~~

## Usage

~~~js
const MemcachedClient = require('libmemcached');

const mcc = new MemcachedClient('--SERVER=127.0.0.1');

console.log(mcc.get('test'));
~~~

## API

### `get(key : String) : Buffer`