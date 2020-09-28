Feature: Hear shout
    Scenario: Listener is within range
        Given Luccy is within 15 meters from Sean
        When Sean shouts "free bagels at Sean"
        Then Luccy hears Sean's message