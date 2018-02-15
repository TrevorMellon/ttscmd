 [![Build status](https://ci.appveyor.com/api/projects/status/94cwfhgotu1a053h?svg=true)](https://ci.appveyor.com/project/TrevorMellon/ttscmd) [![Coverity Status](https://scan.coverity.com/projects/15071/badge.svg)](https://scan.coverity.com/projects/trevormellon-ttscmd)

# ttscmd
Microsoft SAPI Interface for enumerating voice tokens and companion command line text-to-speech (TTS) app. 
Fuzzy evaluation for age, gender, name so as to get the closest voice possible.

# Commandline Options

### Primary Options:
*  -v [ --version ]                      Display version information
*  -h [ --help ]                         Show help information
*  -s [ --say ] arg (=What would you like me to say?)
                                        Speak the following text

### List Options:
*  -l [ --list ]                         List voices installed on the system
*  -j [ --json ]                         Use json output

### Search Options:
*  --age arg                             Based on age
*  --gend arg                            Based on gender
*  --lang arg                            Based on language code
*  --name arg                            Based on voice name
*  --vend arg                            Based on voice vendor

### Input/Output Options:
*  --wav arg                             Write to wav file instead of speakers

## Transifex Project
[transifex.com](https://www.transifex.com/trevor-mellon/ttscmd)
