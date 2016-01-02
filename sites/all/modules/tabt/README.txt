CONTENTS OF THIS FILE
---------------------

 * Summary
 * Installation
 * Configuration
 * PHP Functions
 
 SUMMARY
 --------------
 With this module provides the basic functionality to look up results from a
 TabT-powered, a free Table Tennis Manager, site and display it on your own
 Drupal site.
 
 To submit bug reports and feature suggestions, or to track changes:
  https://drupal.org/project/issues/1288180
 
 REQUIREMENTS
 --------------
 
   * An Account on the TabT-Site you are going to use.
     (default http://competitie.vttl.be/)
   * PHP Soap Extension on your webserver.
     (http://php.net/manual/en/book.soap.php)
   
 INSTALLATION
 --------------
 
   * Install as usual. See https://drupal.org/node/895232 for further
     instructions.
 
 CONFIGURATION
 --------------
 
  
    * TabT-API: The url to the TabT-API.
    * Link to Club: Choose whether you want to link your site to a club. If you
      do so, you can use all functionality, but you can only view data about
      teams of your club.
      If you choose not to link to a club, you will only be able to use a
      limited functionality (e.g. division rankings), but you can do this for
      all divisions. See the submodules for more information.
    * Club-ID: Enter your Club-ID (eg. Vl-B123).
    * Clubname: Enter your Clubname. This should not be your full clubname, but
      as it is displayed on Rankings. If the module is unable to indicate the
      rank of your teams, this setting is wrong.
    * Competition Site: Change this if you are using a different TabT-site.
      (default: competitie.vttl.be)
    * TabT Teams path: This is the path of the teamslist. (default: teams)
    * Locale: If you wish to use this module in a different language, enter the
      right setting here to show dates in the right language.
    * Caching: Check this if you want to temporary cache (store) data gathered.
      This greatly improves performance, but it causes a delay in showing
      changes. (default: disabled)
               
  2. Go to admin/config/services/tabt/credentials and enter your logindetails for the
     TabT Site.
  
    Note: The language of this account determines the language of certain
    returned data. To change the language, log in at the TabT-site and change
    your language.
    
  3. Go to admin/config/services/tabt/teams and enter an alias for each team. If you do
     not enter an alias, you will have to use the team-ID to reference to it.
     Examples of aliases are the teamletter.
     Note: this page will be disabled if you chose not to link to a club.
    
  4. Enable any of the submodules and configure them.
  
    * See the README in each module.

 PAGES
 --------------
   The following pages are available in this module:

   1. Teamspage
     * This page shows an overview of all the teams in your club.
       If you have enabled the matches module, links will be provided to the
       rankings and calendars.
     * URL: teams (default), can be changed in the configuration.
       Note: This page will only be available if you chose to link to a club.
    
 THEMING
 --------------
   You can theme the Teamspage with theme functions.
   
   1. Teamspage
     * Theme: tabt_teams
     * Variable: teams: array of TeamEntry-objects
       See http://api.frenoy.net/tabtapi-doc/classTeamEntry.html for more
       details.
       Note: Data in this object is not sanitized. For more info, see
       https://drupal.org/writing-secure-code
     * Variable: season: The number of the season being viewed.
 