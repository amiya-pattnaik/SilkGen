[ ] //All ebay windows are declared here.
[ ] 
[+] winclass 	Ebay :	BrowserChild
	[ ] 
	[+] VOID Invoke()
		[+] //Method Info:
			[ ] // function  	: Invoke()
			[ ] // returns   	: VOID
			[ ] // parameter 	: None
			[ ] // notes		: Invoke the application's Login page.
			[ ] 							
		[ ] 
		[+] if(!Browser.Exists(1))
			[ ] Browser.Invoke()
		[ ] Browser.SetActive()
		[ ] // Loading the Application URL
		[ ] Browser.LoadPage(sURL)
		[ ] Browser.WaitForReady(180)
		[ ] Browser.Maximize()
		[ ] 
		[ ] //Browser.WaitForReady(300)
		[ ] Sleep(20)
		[ ] 
		[ ] 
	[ ] 
	[+] VOID Login ()
		[ ] 
		[ ] Invoke()
		[ ] //Clicking the Sighin link to get the required loging page
		[ ] this.SetActive( )
		[ ] this.SignIn.Click ()
		[ ] Browser.WaitForReady(300)
		[ ] //Sleep(10)
		[ ] 
		[+] if (!WelcomeToEBay.Exists(30))
			[ ] Browser.WaitForReady(300)
			[ ] //Sleep(2)
			[ ] 
		[ ] 
		[ ] WelcomeToEBay.SetActive()
		[ ] WelcomeToEBay.UserID.ClearText()
		[ ] WelcomeToEBay.UserID.SetText(mExcelData.sUserName)
		[ ] WelcomeToEBay.Password.SetText(mExcelData.sPassword)
		[ ] WelcomeToEBay.SignedIn.Click ()
		[ ] 
	[ ] 
	[+] VOID VerifyLogin (STRING sUserID)
		[ ] 
		[ ] //Verify the said user is loged in or not
		[+] if (Upper(EBayMessage.User.GetText()) == "HI, ({Upper(mExcelData.sUserName)})!")  //Hi, (test_ctsuser)!
			[ ] Print ("You have successfully Loged in with user {mExcelData.sUserName}")
		[+] else
			[ ] LogError("You are not successfully Loged in")
			[ ] 
		[ ] 
	[ ] 
	[ ] 
	[+] // VOID Login(BOOLEAN bRememberPassword optional,STRING sConnectionString optional, STRING sTestCaseID optional)
		[+] // //Method Info:
			[ ] // // function		: Login()
			[ ] // // returns   	: VOID
			[ ] // // parameter 	: None
			[ ] // // notes		: Login the application with user name and password given in the spreed sheet
			[ ] // 
		[ ] // 
		[ ] // //Variable Declarations
		[ ] // STRING sUserName
		[ ] // STRING sPassword
		[ ] // 
		[+] // if(!CADV_Login.Exists(2))
			[+] // if(AnyCADVPage.Exists(1))
				[ ] // Browser.Close()
				[ ] // 
			[+] // if(!Browser.Exists(1))
				[ ] // Browser.Invoke()
			[ ] // Browser.LoadPage(URL)
			[ ] // SQ_WaitForWindow(this)
		[+] // else
			[ ] // this.SetActive()
		[ ] // 
		[ ] // // // Checks that the test case ID is not NULL
		[+] // // if IsNull (sTestCaseID) && !IsNull(sConnectionString)
			[ ] // // LogError("ERROR: The Test Case ID is null for the Smoke Test script")
		[ ] // // 
		[ ] // // // Checks if the sConnection string is not NULL
		[+] // // if IsNull(sConnectionString)
			[ ] // // // Assign the record values to the username and password variables
			[ ] // // sUserName = mrRecord.rCommon.sUserName
			[ ] // // sPassword = mrRecord.rCommon.sPassword
			[+] // // if (sUserName == NULL)
				[ ] // // sUserName = ""
			[+] // // if (sPassword == NULL)
				[ ] // // sPassword = ""
			[ ] // // 
		[+] // // else
			[ ] // // //Fetches data from Excelsheet and assign to variables
			[ ] // // sUserName = SQ_GetTestCaseData(sConnectionString,sTestCaseID,"UserName")
			[ ] // // sPassword = SQ_GetTestCaseData(sConnectionString,sTestCaseID,"Password")
		[ ] // // 
		[ ] // // // Clears the text in the username and password text box
		[+] // // if(!(bRememberPassword))
			[ ] // // this.UserName.ClearText()
			[ ] // // this.Password.ClearText()
		[ ] // // 
		[ ] // // // For partially authinticated
		[+] // // if (bValidLogin)			
			[+] // // if(sUserName!= NULL )
				[ ] // // this.UserName.SetText(sUserName)
			[+] // // if(sPassword!= NULL)
				[ ] // // this.Password.SetText(sPassword)
		[+] // // else
			[+] // // if(this.UserName.GetText() == NULL || (this.UserName.GetText()) == "")
				[ ] // // this.UserName.SetText(sUserName)
			[ ] // // this.Password.SetText(sPassword)
			[ ] // // bValidLogin = TRUE
		[ ] // // 
		[ ] // // // Checks the "Remember Me" check box
		[+] // // if(bRememberPassword)
			[ ] // // this.RememberMe.Check()
		[ ] // // 
		[ ] // // this.LoginButton.Click()
		[ ] // // 
		[ ] // // //Handles Browser Message window
		[ ] // // HandleBrowserMessages ()
		[ ] // // Sleep(2)
		[ ] // // Browser.WaitForReady(180)
		[ ] // 
	[ ] 
	[ ] //Standard Header//
	[+] HtmlImage	EbayLogo
		[+] multitag "From collectibles to cars, buy and sell all kinds of items on eBay"
			[ ] "$http:??pics.ebaystatic.com?aw?pics?in?logos?logoEbay_x45.gif"
	[+] HtmlLink 	SignOut
		[+] multitag "Sign out"
			[ ] "$https:??signin.ebay.in?ws?eBayISAPI.dll?SignIn"
			[ ] "#8"
			[ ] 
	[+] HtmlLink 	Buy
		[+] multitag "Buy"
			[ ] "#1"
			[ ] "$http:??hub.ebay.in?buy"
	[+] HtmlLink 	Sell
		[+] multitag "Sell"
			[ ] "#2"
			[ ] "$http:??sell.ebay.in?sell"
	[+] HtmlLink 	MyEBay
		[+] multitag "My eBay"
			[ ] "#3"
			[ ] "$http:??my.ebay.in?ws?eBayISAPI.dll?MyEbay&gbh=1"
	[+] HtmlLink 	Community
		[+] multitag "Community"
			[ ] "#4"
			[ ] "$http:??hub.ebay.in?community"
	[+] HtmlLink 	HelpHeader
		[+] multitag "Help[1]"
			[ ] "#5"
			[ ] "$http:??pages.ebay.in?help?index.html[1]"
	[ ] 
	[+] HtmlLink 	MyShoppingCart
		[+] multitag "My Shopping Cart"
			[ ] "#8"
			[ ] "$http:??orders.ebay.in?ws?eBayISAPI.dll?ShoppingCartMgmt"
	[+] HtmlLink 	MyPaisaPay
		[+] multitag "My PaisaPay"
			[ ] "#9"
			[ ] "$http:??orders.ebay.in?ws?eBayISAPI.dll?MyPaisaPaySummary"
	[+] HtmlLink 	ContactUs
		[+] multitag "Contact Us[1]"
			[ ] "#10"
			[ ] "$http:??pages.ebay.in?help?contact_us?_base?index.html"
	[+] HtmlLink 	SiteMapHeader
		[+] multitag "Site Map[1]"
			[ ] "#11"
			[ ] "$http:??pages.ebay.in?sitemap.html[1]"
	[ ] //End of Standard Header//
	[ ] 
	[ ] //Standard Footer//
	[+] HtmlLink 	AboutEBay
		[+] multitag "About eBay"
			[ ] "#20"
			[ ] "$http:??pages.ebay.in?aboutebay.html"
	[+] HtmlLink 	Announcements
		[+] multitag "Announcements"
			[ ] "#21"
			[ ] "$http:??www2.ebay.com?aw?marketing-in.shtml"
	[+] HtmlLink 	Register
		[+] multitag "register"
			[ ] "register[1]"
			[ ] "^Sign in"
	[+] HtmlLink 	SecurityResolutionCentre
		[+] multitag "Security  Resolution Centre"
			[ ] "#23"
			[ ] "$http:??pages.ebay.in?securitycentre?index.html"
	[+] HtmlLink 	FeedbackForum
		[+] multitag "Feedback Forum"
			[ ] "#24"
			[ ] "$http:??pages.ebay.in?services?forum?feedback.html"
	[+] HtmlLink 	SiteMapFooter
		[+] multitag "Site Map[2]"
			[ ] "#25"
			[ ] "$http:??pages.ebay.in?sitemap.html[2]"
	[+] HtmlLink 	HelpFooter
		[+] multitag "Help[2]"
			[ ] "#26"
			[ ] "$http:??pages.ebay.in?help?index.html[2]"
	[+] HtmlLink 	UserAgreement
		[+] multitag "User Agreement"
			[ ] "#28"
			[ ] "$http:??pages.ebay.in?help?policies?user-agreement.html"
	[+] HtmlLink 	PrivacyPolicy
		[+] multitag "Privacy Policy"
			[ ] "#29"
			[ ] "$http:??pages.ebay.in?help?policies?privacy-policy.html"
	[+] HtmlLink 	EBayOfficialTime
		[+] multitag "eBay official time"
			[ ] "#30"
			[ ] "$http:??viv.ebay.in?ws?eBayISAPI.dll?EbayTime"
	[+] HtmlLink 	Copyright©19952009EBayInc3
		[+] multitag "Copyright © 1995-2009 eBay Inc. All Rights Reserved. Designated trademarks and brands are the property of their respective own*"
			[ ] "#27"
			[ ] "$https:??seal.verisign.com?splash?form_file=fdf?splash.fdf&dn=SC"
	[+] HtmlLink 	AboutSSLCertificates
		[+] multitag "About SSL Certificates"
			[ ] "#31"
			[ ] "$http:??www.verisign.com?ssl-certificate"
	[ ] 
	[+] HtmlText 	Copyright©19952009EBayInc1
		[ ] tag "Copyright © 1995-2009 eBay Inc. All Rights Reserved. Designated trademarks and brands are the property of their respective own*"
	[+] HtmlImage 	Copyright©19952009EBayInc2
		[+] multitag "Copyright © 1995-2009 eBay Inc. All Rights Reserved. Designated trademarks and brands are the property of their respective own*"
			[ ] "#10"
			[ ] "$http:??pics.ebaystatic.com?aw?pics?in?s.gif[2]"
	[+] HtmlImage 	VerisignSeal
		[+] multitag "Verisign Seal"
			[ ] "#9"
			[ ] "$http:??pics.ebaystatic.com?aw?pics?in?logos?logoVeriSign_100x65"
	[ ] //End of Footer Information//
	[ ] 
	[ ] 
	[ ] //**** SubNavigational Links
	[ ] 
	[ ] //**** Common window objects for Ebay
	[ ] 
	[ ] 
	[ ] 
	[ ] 
	[ ] 
	[ ] 
[ ] 
[ ] 
[-] window 	Ebay 	EBayHome
	[ ] tag "eBay India - Online Shopping Mall: Free Auctions, Shop?Buy?Sell Mobiles, Cameras, Apparel, Computers, Bollywood Clothes  Indi*"
	[ ] parent Browser
	[ ] 
	[ ] //Header Info
	[+] HtmlLink 	SignIn
		[-] multitag "Sign in"
			[ ] "#11"
			[ ] "$https:??signin.ebay.in?ws?eBayISAPI.dll?SignIn"
	[+] HtmlLink 	Register1
		[+] multitag "register[1]"
			[ ] "#12"
			[ ] "$https:??scgi.ebay.in?ws?eBayISAPI.dll?RegisterEnterInfo"
		[ ] 
	[+] HtmlImage 	WelcomeOr2
		[+] multitag "Welcome!  or"
			[ ] "#5"
			[ ] "$http:??pics.ebaystatic.com?aw?pics?in?cart.gif"
	[ ] 
	[ ] //{{HtmlLink, Sign in|#11|$https:??signin.ebay.in?ws?eBayISAPI.dll?SignIn, 1}, {HtmlLink, register[1]|#12|$https:??scgi.ebay.in?ws?eBayISAPI.dll?RegisterEnterInfo, 1}}
[ ] 
[+] window 	Ebay 	WelcomeToEBay
	[ ] tag "Welcome to eBay"
	[ ] parent Browser
	[ ] 
	[+] HtmlLink 		IForgotMyPassword
		[+] multitag "I forgot my password"
			[ ] "#3"
			[ ] "$https:??scgi.ebay.in?ws?eBayISAPI.dll?FYPShow"
	[+] HtmlLink 		IForgotMyUserID
		[+] multitag "I forgot my user ID"
			[ ] "#2"
			[ ] "$http:??cgi4.ebay.in?ws?eBayISAPI.dll?UserIdRecognizerShow"
	[ ] 
	[+] HtmlText 		SignedIn
		[ ] tag "Sign in"
	[+] HtmlText 		UserID1
		[ ] tag "User ID"
	[+] HtmlText 		Password1
		[ ] tag "Password"
	[ ] 
	[+] HtmlTextField 	UserID
		[+] multitag "User ID"
			[ ] "#1"
			[ ] "$userid"
	[+] HtmlTextField 	Password
		[+] multitag "Password"
			[ ] "#2"
			[ ] "$pass"
	[ ] 
	[+] HtmlPushButton 	SigneIn
		[+] multitag "Keep me signed in for today. Don't check this box if you're at a public or shared computer."
			[ ] "#2"
	[ ] 
[ ] 
[+] window 	Ebay 	RegisterPage
	[ ] tag "Register as an eBay member"
	[ ] parent Browser
	[ ] 
	[+] LIST OF WINDOW lwPageContents = {...}
		[ ] this.FirstName
		[ ] this.LastName
		[ ] this.HomeAddress
		[ ] this.City
		[ ] this.State
		[ ] this.PinCode
		[ ] this.CountryOrRegion
		[ ] this.TelephoneNumber
		[ ] this.EmailAddress
		[ ] this.ReEnterYourEmailAddress
		[ ] this.CreateYourEBayUserID
		[ ] this.CheckYourUserID
		[ ] this.CreateYourPassword
		[ ] this.ReEnterYourPassword
		[ ] this.Register
	[ ] 
	[ ] //Methods
	[+] VOID Invoke ()
		[ ] EBayHome.Invoke ()
		[ ] 
		[ ] EBayHome.Register.Click ()
		[ ] Browser.WaitForReady (300)
	[ ] 
	[ ] 
	[ ] 
	[+] HtmlTextField FirstName
		[+] multitag "First name"
			[ ] "#1"
			[ ] "$firstname"
	[+] HtmlTextField LastName
		[+] multitag "Last name"
			[ ] "#2"
			[ ] "$lastname"
	[+] HtmlTextField HomeAddress
		[+] multitag "Home address[1]"
			[ ] "#3"
			[ ] "$address1"
	[+] HtmlTextField City
		[+] multitag "City"
			[ ] "#5"
			[ ] "$city"
	[+] HtmlPopupList State
		[+] multitag "State"
			[ ] "#1"
			[ ] "$state"
	[+] HtmlTextField PinCode
		[+] multitag "Pin Code"
			[ ] "#6"
			[ ] "$zip"
	[+] HtmlPopupList CountryOrRegion
		[+] multitag "Country or region"
			[ ] "#2"
			[ ] "$countryId"
	[+] HtmlTextField TelephoneNumber
		[+] multitag "Primary telephone number"
			[ ] "#7"
			[ ] "$dayphone1"
	[+] HtmlTextField EmailAddress
		[+] multitag "Email address"
			[ ] "#8"
			[ ] "$email"
	[+] HtmlTextField ReEnterYourEmailAddress
		[+] multitag "Re-enter your email address"
			[ ] "#9"
			[ ] "$retype_email"
	[+] HtmlTextField CreateYourEBayUserID
		[+] multitag "Create your eBay user ID"
			[ ] "#10"
			[ ] "$userid"
	[+] HtmlPushButton CheckYourUserID
		[+] multitag "Check your user ID"
			[ ] "#1"
			[ ] "$CheckUserId"
	[+] HtmlTextField CreateYourPassword
		[+] multitag "Create your password"
			[ ] "#11"
			[ ] "$pass"
	[+] HtmlTextField ReEnterYourPassword
		[+] multitag "Re-enter your password"
			[ ] "#12"
			[ ] "$rpass"
	[+] HtmlPopupList PickASecretQuestion
		[+] multitag "Pick a secret question"
			[ ] "#3"
			[ ] "$canned"
	[+] HtmlTextField YourSecretAnswer
		[+] multitag "Your secret answer"
			[ ] "#13"
			[ ] "$myanswer"
	[+] HtmlPopupList DateofBirth
		[+] multitag "Your date of birth[1]"
			[ ] "#4"
			[ ] "$birthdate1"
	[+] HtmlPopupList MonthofBirth
		[+] multitag "Your date of birth[2]"
			[ ] "#5"
			[ ] "$birthdate2"
	[+] HtmlTextField Year
		[+] multitag "Year"
			[ ] "#14"
			[ ] "$birthdate3"
	[+] BrowserChild EBayTheWorldSOnlineMark
		[ ] tag "eBay - The World's Online Marketplace"
		[+] HtmlMeta ContentType
			[+] multitag "Content-Type"
				[ ] "#1"
				[ ] "$text?html; charset=UTF-8"
		[+] HtmlImage HttpsScgiEbayInWsEBayIS
			[+] multitag "#1"
				[ ] "$https:??scgi.ebay.in?ws?eBayISAPI.dll?LoadBotImage&tokenString="
		[+] HtmlHidden Tokenstring
			[+] multitag "#1"
				[ ] "$tokenstring"
		[+] HtmlImage I_sGauge
			[+] multitag "#2"
				[ ] "$i_sGauge"
	[+] HtmlTextField PleaseEnterTheVerificatio
		[+] multitag ", please enter the verification code hidden in the image."
			[ ] "#15"
			[ ] "$tokentext"
	[+] HtmlHidden Tokenstring4
		[+] multitag "#125"
			[ ] "$tokenstring[4]"
	[+] HtmlText PleaseEnterTheVerification
		[+] multitag "Please enter the verification code"
			[ ] "$div1_tokentext"
	[+] HtmlLink RefreshTheImage
		[+] multitag "Refresh the image"
			[ ] "#11"
			[ ] "$linkBotRefresh"
	[+] HtmlLink ListenToTheVerificationCod
		[+] multitag "Listen to the verification code"
			[ ] "#12"
			[ ] "$linkBotListen"
	[+] HtmlText PleaseClickOnTheHyper1
		[ ] tag "(  )(please click on the hyperlinks as underlined below)"
	[+] HtmlText EBayUserAgreementTheEBay
		[ ] tag "eBay User Agreement, the eBay Rules  Policies  the Privacy Policy"
	[+] HtmlLink PrinterFriendlyVersion
		[+] multitag "Printer-friendly version"
			[ ] "#13"
			[ ] "$http:??pages.ebay.in?help?policies?uapp.html"
	[+] HtmlImage TermsOfUseAndYourPrivacy2
		[+] multitag "Terms of use and your privacy[1]"
			[ ] "#7"
			[ ] "$https:??securepics.ebaystatic.com?aw?pics?s.gif[5]"
	[+] HtmlText PleaseCheckTheBoxBelow1
		[ ] tag "Please check the box below:[1]"
	[+] HtmlImage TermsOfUseAndYourPrivacy3
		[+] multitag "Terms of use and your privacy[2]"
			[ ] "#8"
			[ ] "$https:??securepics.ebaystatic.com?aw?pics?s.gif[6]"
	[+] HtmlCheckBox ThatByClickingOnTheBoxI1
		[+] multitag "That by clicking on the box I agree that I have read and understood the[1]"
			[ ] "#1"
			[ ] "$acceptq1"
	[+] HtmlImage PleaseClickOnTheHyper2
		[+] multitag "(  )(please click on the hyperlinks as underlined below)"
			[ ] "#9"
			[ ] "$https:??securepics.ebaystatic.com?aw?pics?s.gif[7]"
	[+] HtmlImage TermsOfUseAndYourPrivacy4
		[+] multitag "Terms of use and your privacy[3]"
			[ ] "#10"
			[ ] "$https:??securepics.ebaystatic.com?aw?pics?s.gif[8]"
	[+] HtmlText ThatByClickingOnTheBoxI2
		[ ] tag "That by clicking on the box I agree that I have read and understood the ,    (hereinafter referred as the ?User Agreement  e*"
	[+] HtmlLink EBayUserAgreement
		[+] multitag "eBay User Agreement"
			[ ] "#14"
			[ ] "$http:??pages.ebay.in?help?policies?ebay-user-agreement.html"
	[+] HtmlLink TheEBayRulesPolicies
		[+] multitag "the eBay Rules  Policies"
			[ ] "#15"
			[ ] "$http:??pages.ebay.in?help?policies?ebay-rules-policy.html"
	[+] HtmlLink ThePrivacyPolicy
		[+] multitag "the Privacy Policy"
			[ ] "#16"
			[ ] "$http:??pages.ebay.in?help?policies?ebay-privacy-policy.html"
	[+] HtmlImage TermsOfUseAndYourPrivacy5
		[+] multitag "Terms of use and your privacy[4]"
			[ ] "#11"
			[ ] "$https:??securepics.ebaystatic.com?aw?pics?s.gif[9]"
	[+] HtmlList HereinafterReferredAsThe1
		[ ] tag "(hereinafter referred as the ?User Agreement  eBay Policies?) and unconditionally accept to be legally bound by the followin*"
		[+] HtmlText ThatIHaveHadReasonableOpp
			[ ] tag "That I have had reasonable opportunity and time to read, understand and take proper advice;"
		[+] HtmlText ThatWhileUsingTheServices
			[ ] tag "That while using the services  facilities on the eBay Website www.ebay.in, I unequivocally agree  undertake to abide by and *"
		[+] HtmlText IAgreeThatTheUserAgreemen
			[ ] tag "I agree that the User Agreement  eBay Policies are in all respects fair, reasonable and necessary in order to protect the use*"
		[+] HtmlText IAgreeThatIHaveProvidedT
			[ ] tag "I agree that I have provided true, accurate, current and complete information about myself as prompted by eBay's registration *"
		[+] HtmlText IAgreeThatEBayIsOnlyProv
			[ ] tag "I agree that eBay is only providing a platform for communication and it is agreed that the contract for sale of any of the pro*"
		[+] HtmlText N11
			[ ] tag "-[1]"
		[+] HtmlImage N12
			[+] multitag "-[1]"
				[ ] "#1"
				[ ] "$https:??securepics.ebaystatic.com?aw?pics?s.gif[1]"
		[+] HtmlImage N21
			[+] multitag "-[2]"
				[ ] "#2"
				[ ] "$https:??securepics.ebaystatic.com?aw?pics?s.gif[2]"
		[+] HtmlText IAcceptThatTheMannerTerm
			[ ] tag "I accept that the manner, terms and conditions of delivery, payment, insurance etc. are to be independently agreed upon when t*"
		[+] HtmlText N22
			[ ] tag "-[2]"
		[+] HtmlImage N3
			[+] multitag "-[3]"
				[ ] "#3"
				[ ] "$https:??securepics.ebaystatic.com?aw?pics?s.gif[3]"
		[+] HtmlImage N4
			[+] multitag "-[4]"
				[ ] "#4"
				[ ] "$https:??securepics.ebaystatic.com?aw?pics?s.gif[4]"
		[+] HtmlText AtNoTimeShallAnyRightTi
			[ ] tag "At no time shall any right, title or interest over the items vest with eBay nor shall eBay have any obligations or liabilitie*"
		[+] HtmlText IUnderstandThatTheInformat
			[ ] tag "I understand that the information I provide will be collected by eBay International AG and stored and processed by eBay Inc. l*"
	[+] HtmlImage TermsOfUseAndYourPrivacy6
		[+] multitag "Terms of use and your privacy[5]"
			[ ] "#12"
			[ ] "$https:??securepics.ebaystatic.com?aw?pics?s.gif[10]"
	[+] HtmlText PleaseClickOnTheHyperlink
		[ ] tag "(please click on the hyperlinks as underlined below)"
	[+] HtmlText PaisaPayUserAgreement1
		[ ] tag "PaisaPay User Agreement"
	[+] HtmlImage TermsOfUseAndYourPrivacy7
		[+] multitag "Terms of use and your privacy[6]"
			[ ] "#13"
			[ ] "$https:??securepics.ebaystatic.com?aw?pics?s.gif[11]"
	[+] HtmlText PleaseCheckTheBoxBelow2
		[ ] tag "Please check the box below:[2]"
	[+] HtmlImage TermsOfUseAndYourPrivacy8
		[+] multitag "Terms of use and your privacy[7]"
			[ ] "#14"
			[ ] "$https:??securepics.ebaystatic.com?aw?pics?s.gif[12]"
	[+] HtmlCheckBox ThatByClickingOnTheBoxI3
		[+] multitag "That by clicking on the box I agree that I have read and understood the[2]"
			[ ] "#2"
			[ ] "$acceptq5"
	[+] HtmlImage TermsOfUseAndYourPrivacy9
		[+] multitag "Terms of use and your privacy[8]"
			[ ] "#15"
			[ ] "$https:??securepics.ebaystatic.com?aw?pics?s.gif[13]"
	[+] HtmlText ThatByClickingOnTheBoxI4
		[ ] tag "That by clicking on the box I agree that I have read and understood the  (hereinafter referred as the (?PaisaPay UA?) and unco*"
	[+] HtmlLink PaisaPayUserAgreement2
		[+] multitag "PaisaPay User Agreement"
			[ ] "#17"
			[ ] "$http:??pages.ebay.in?help?policies?pspx-user-agreement.html"
	[+] HtmlImage TermsOfUseAndYourPrivacy10
		[+] multitag "Terms of use and your privacy[9]"
			[ ] "#16"
			[ ] "$https:??securepics.ebaystatic.com?aw?pics?s.gif[14]"
	[+] HtmlList HereinafterReferredAsThe2
		[ ] tag "(hereinafter referred as the (?PaisaPay UA?) and unconditionally accept to be legally bound by the following:"
	[+] HtmlPushButton ThatByClickingOnTheBoxI5
		[+] multitag "That by clicking on the box I agree that I have read and understood the  (hereinafter referred as the (?PaisaPay UA?) and unco*"
			[ ] "#2"
			[ ] "$continue"
	[+] HtmlText Register
		[ ] tag "Register"
	[+] HtmlText WeNeedSomeAdditionalInform
		[+] multitag "We need some additional information from you. Please check and try again."
			[ ] "$regerrorDiv"
[ ] 
[+] window 	Ebay 	EBayMessage
	[ ] tag "eBay Message"
	[ ] parent Browser
	[ ] 
	[+] HtmlHeading MessageFromEBay
		[ ] tag "Message from eBay"
	[+] HtmlText 	User
		[+] multitag "#4"
			[ ] "Hi, (*)!"
	[ ] 
	[ ] 
	[ ] 
[ ] 
[+] window	Ebay	AnyEbayPage 
	[ ] tag "*/[HtmlImage]From collectibles to cars, buy and sell all kinds of items on eBay/.."
	[ ] //"$http:??pics.ebaystatic.com?aw?pics?in?logos?logoEbay_x45.gif"
	[ ] parent Browser
	[ ] 
	[ ] //Methods
	[+] VOID Logout()
		[+] //Method Info:
			[ ] // Method		: Logout()
			[ ] // Returns   	: VOID
			[ ] // Parameter 	: None
			[ ] // notes		: Logout from the application by clicking logout link in the header ofthe page
			[ ] 
		[ ] this.SignOut.Click()
		[ ] 
[ ] 
[+] window 	Ebay 	EbayLogoutPage
	[ ] tag "You've signed out. See you again soon!"
	[ ] parent Browser
	[ ] 
	[ ] //Methods
	[+] VOID VerifyLogout ()
		[ ] Verify (this.LogoutMessage.Exists(),TRUE,"Logout Verification:")
	[ ] 
	[ ] 
	[+] HtmlText LogoutMessage
		[+] multitag "You've signed out. See you again soon!"
			[ ] "^Advanced Search"
			[ ] "#5"
[ ] 
[ ] 
