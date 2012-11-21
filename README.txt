-- SUMMARY --

  This module is a plugin for Addressfield and provides support for Portuguese addresses to Drupal's Addressfield (http://www.drupal.org/project/addressfield)
  The Portuguese Address Field contains a hierarchical select for the District (distrito), Locality (concelho) and Parish (freguesia).
  
  The list with districts, localities and parishes is based on the CAOP 2011 (http://www.igeo.pt/produtos/cadastro/caop/inicial.htm) from the Instituto Geográfico Português (http://www.igeo.pt/)
  
  There are field for District, Locality and Parish, but when rendering the address the District and Parish fields are hidden.

-- INSTALLATION --

  * Install as usual.
  
  * Activate as a regual Addressfield format plugin


-- CONFIGURATION -- 

  * In the field configuration, make sure that the following Format Handlers are enabled: 'Address form (country specific)' & 'Address form (Portugal add-on)'
  
  * Currently there is a bug in Address Field that causes the Format Handler not to load when only one country is selected. 
    If you want to restrict country selection to Portugal, please make sure to also enable the format handler 'Hide the country when only one is available' (See http://www.drupal.org/node/1539744 for more information)
    Or apply patch (https://drupal.org/node/1539744#comment-6721664) to Addressfield.