# libexadrums.js

Javascript bindings for libexadrums.

## Before you start

First of all, you need to install libexadrums as well as its headers.
Some Linux distributions distribute exadrums. If you're using such a distribution, you can install libexadrums-dev easily:

```bash
sudo apt install libexadrums-dev
```

If your Linux distribution doesn't include exadrums, you'll have to build the library yourself. Please refer to the official libexadrums repository and follow the instructions: https://github.com/SpintroniK/libeXaDrums.

## How to install

If you've already installed libexadrums-dev, you can now install the package using yarn or npm:

```bash
yarn install
```

## How to use

In order to use the exadrums library, you'll need to get some data to configure it.
Fortunately, there's a repo for that: https://github.com/SpintroniK/exadrums-data.
The easiest way to install the configuration is to download it directly from the repository, and unzip it into your configuration folder:

```bash
wget https://github.com/SpintroniK/exadrums-data/archive/refs/heads/master.zip
unzip master.zip -d exadrumsConfig
```

It's now time to write some javascript.
First of all, you need to import the javascript bindings:

```js
const LibexadrumsJs = require("@exadrums/libexadrums.js/lib/binding.js")
```

But before you rush into it, there's one more thing you need to do.
Take a look at the `sensorsConfig.xml` file, and replace the `<HddDataFolder>./Data/</HddDataFolder>` line by the the configuration folder path (and don't forget the trailing slash). The file contents should look like this:

```xml
<SensorsConfig>
    <SamplingRate>2000000</SamplingRate>
    <Resolution>12</Resolution>
    <Type>Hdd</Type>
    <HddDataFolder>./exadrumsConfig/exadrums-data-master/</HddDataFolder>
</SensorsConfig>
```

Then, you can use `LibexadrumsJs` just like any javascript module.
Here is a brief example that shows how to start the exadrums module in javascript (you can even type that code directly into the nodejs console):

```js
const LibexadrumsJs = require("@exadrums/libexadrums.js/lib/binding.js")

const exadrums = new LibexadrumsJs.Exadrums('./exadrumsConfig/exadrums-data-master')

exadrums.start() // Start the drum module

//Do some things here

exadrums.stop() // Stop the drum modules
```

Of course, it's probably more useful to call the `start` and `stop` functions on events, for instance click events.
