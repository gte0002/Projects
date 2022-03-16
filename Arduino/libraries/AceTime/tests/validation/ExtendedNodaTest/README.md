# ExtendedNodaTest

This unit test compares the DST transitions calculated by the
`ExtendedZoneProcessor` class (which uses the `zonedbx` data files) with the
`validation_data.cpp` file generated by the `tools/compare_noda/Program.cs` C#
program using [Noda Time](https://nodatime.org/).

## Requirements

* Install both .NET 5.0 and .NET 3.1
    * https://docs.microsoft.com/en-us/dotnet/core/install/linux-ubuntu
    * .NET 3.1 is required because the `TzdbCompiler` does not run using .NET
      5.0.
    * (It might be possible to install just .NET 5.0. I have not verified this.)
* Clone the Noda Time repo as sibiling to `AceTime`
    * `$ git clone https://github.com/nodatime/nodatime`
    * Update the `NODA_TIME_DIR` parameter in the `Makefile`
* Clone the EpoxyDuino repo as a sibling to `AceTime`
    * `$ git clone https://github.com/bxparks/EpoxyDuino.git`

## Running the Test

The `compare_noda` tool generates about 433,000 data points spanning the year
1974 to 2050. It is too large to run on any Arduino board that I am aware of,
including the ESP32. However it does run on a Linux machine using the
[EpoxyDuino](https://github.com/bxparks/EpoxyDuino) adapter layer.

Assuming that you have `g++` and `make` installed, just type:
```
$ make clean
$ make

$ make runtests
TestRunner started on 268 test(s).
Test ExtendedTransitionTest_Africa_Abidjan passed.
...
Test ExtendedTransitionTest_Pacific_Wallis passed.
Test ExtendedTransitionTest_WET passed.
TestRunner duration: 2.189 seconds.
TestRunner summary: 386 passed, 0 failed, 0 skipped, 0 timed out, out of 386 test(s).

$ make clean
```

## Noda Time Version

The Noda Time library allows the NodaZoneData file to be generated dynamically
from the original IANA TZDB files (https://nodatime.org/3.0.x/userguide/tzdb).
The `$(TZ_VERSION)` in the `Makefile` specifies the TZDB version. The custom TZ
configuration happens in 2 steps:

* `tzdata$(TZ_VERSION).nzd`:
    * The NodaZoneData file is created by runing the `TzdbCompiler` from the
      Noda Time source repo.
    * The `TzdbCompiler` automatically downloads the
      `tar.gz` file from https://data.iana.org/time-zones/releases/.
* `validation_data.json`:
    * The `compare_noda` program is given the `--nzd_file` flag which tells the
      program to look for the NodaZoneData file at the given file path.