Neon
====

This module lets the user enter a URL or a comma separated list of URLs, and
retrieves and saves information from those resources. The module creates a new node type
for the purpose of storing information that is retrieved. This (web scraping) module
is a useful tool for anyone wanting to collect, collate and index information
about other sites on the web.

HOW TO INSTALL:
---------------
- Install this module using the official Backdrop CMS instructions at
https://backdropcms.org/guide/modules

HOW TO USE:
------
- Scrape a single URL at /admin/config/neon/scrape
    * URL - Enter the URL that you want to scrape.
    * NESTED DIV DEPTH - enter a numeral 1 or 2 or whatever to scrape everything
       inside of this nested level.
    * SPECIFIC DIV - enter the name of a div without quotes or <>
       If you wanted everything inside of <div class ='corps'> just enter corps.
    * GET ALL IMAGES - Retrieves the URLs of all images.
    * GET ALL LINKS - Retrieves the URLs of all links.
    * RETURN ENTIRE PAGE - Retrieves the entire source of the document.
    * SHOW LINKS AS CSV LIST - Outputs the link list as a comma separated list.
    * SAVE THIS DATA - Saves the results of the form as a node.

- Scrape a comma separated list of URLs at /admin/config/neon/url_batch
    * COMMA SEPARATED URL LIST - Input csv string
       like https://site1.com,https://site2.com,https://site3.com
    * SAVE BATCH LIST - Save a batch list without processing it until unchecked.
    * RUN BATCH - Immidiately process this batch job, save the results as node content.
    * GET ALL IMAGES - Retrieves the URLs of all images for each site.
    * GET ALL LINKS - Retrieves the URLs of all links for each site.
    * RETURN ENTIRE PAGE - Retrieves the entire source of the document for each site.

LICENSE
---------------    
This project is GPL v2 software. See the LICENSE.txt file in this directory
for complete text.

CURRENT MAINTAINERS
---------------    
- [earlyburg](https://github.com/earlyburg).


CREDITS   
---------------
- This module uses the Simple HTML DOM Parser Library
  * Website: http://sourceforge.net/projects/simplehtmldom/
  * Authors: S.C. Chen, John Schlick, Rus Carroll, logmanoriginal

- [earlyburg](https://github.com/earlyburg).

