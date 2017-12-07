# libmemcached

## Table of contents

* [Requirements](#requirements)
* [Installation](#installation)
* [Usage](#usage)

## Requirements

`libmemcached` and `libmemcached-dev`

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
const memcached = require('libmemcached').Memcache;

const mc = new Memcache('--SERVER=127.0.0.1');

console.log(mc.get('test'));
~~~
