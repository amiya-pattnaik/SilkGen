<?xml version="1.0" encoding="utf-8"?>

<!-- Created by Amiya Pattnayak (pattnaik_amiya@yahoo.com), 02/04/2009 (mm/dd/yy)-->
<!-- Please do not modify this file without prior permission of me -->
<!-- http://www.w3.org/TR/WD-xsl"-->
<xsl:stylesheet 
		xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version= "1.0">

	<xsl:template match="/">
		<xsl:for-each select="SILKGENTD">

			<html>
				<head>
					<title>
						<xsl:value-of select="@title"/>
					</title>
				</head>
				
				<body bgcolor="#FCDFFF" style="font-family: Verdana, Arial; font-size: smaller">
					<h3>
						<xsl:value-of select="@title"/>
					</h3>
						<h2>
						<tr>
							<td width="21%" height="15">
								<font size="1">
									<!-- <b>Copyright:</b> -->
								</font>
							</td>
							<td width="79%" height="15">
								<font size="1">
									<xsl:value-of select="@copyright"/>
								</font>
							</td>
						</tr>
						</h2>
					<hr/>
					
					<table border="0" width="100%" height="51">
										
						<tr>
							<td width="21%" height="15">
								<font size="1">
									<b>Created:</b>
								</font>
							</td>
							<td width="79%" height="15">
								<font size="1">
									<xsl:value-of select="CREATION_DATE"/>
								</font>
							</td>
						</tr>
						<tr>
							<td width="21%" height="15">
								<font size="1">
									<b>Operating System:</b>
								</font>
							</td>
							<td width="79%" height="15">
								<font size="1">
									<xsl:value-of select="OS"/>
								</font>
							</td>
						</tr>
						<tr>
							<td width="21%" height="15">
								<font size="1">
									<b>Host Name:</b>
								</font>
							</td>
							<td width="79%" height="15">
								<font size="1">
									<xsl:value-of select="HOSTNAME"/>
								</font>
							</td>
						</tr>
						<tr>
							<td width="21%" height="15">
								<font size="1">
									<b>Test User:</b>
								</font>
							</td>
							<td width="79%" height="15">
								<font size="1">
									<xsl:value-of select="TESTUSER"/>
								</font>
							</td>
						</tr>						
						<tr>
							<td width="21%" height="15" bgcolor="#d3d3d3">
								<font size="1">
									<b>Total:</b>
								</font>
							</td>
							<td width="79%" height="15" bgcolor="#d3d3d3">
								<font size="1">
									<xsl:value-of select="count(PROJECT/TESTLIST/TEST)"/>
								</font>
							</td>
						</tr>							
						<tr>
							<td width="21%" height="15" bgcolor="#98fb98">
								<font size="1">
									<b>Passed:</b>
								</font>
							</td>
							<td width="79%" height="15" bgcolor="#98fb98">
								<font size="1">
									<xsl:value-of select="count(PROJECT/TESTLIST/TEST[@status='Passed'])"/>
								</font>
							</td>
						</tr>						
						<tr>
							<td width="21%" height="15" bgcolor="#db7093">
								<font size="1">
									<b>Failed:</b>
								</font>
							</td>
							<td width="79%" height="15" bgcolor="#db7093">
								<font size="1">
									<xsl:value-of select="count(PROJECT/TESTLIST/TEST[@status='Failed'])"/>
								</font>
							</td>
						</tr>							
					</table>
					
					<xsl:for-each select="PROJECT">
						<p>
						<b>Project:</b>
						<xsl:value-of select="@name"/>
						</p>
						
					<xsl:apply-templates/>
						
					<!-- Change by Amiya on 13/02/09-->
					<xsl:for-each select="TESTLIST/TEST/STEP/OPERATION">
							
							<table border="0" width="100%" bgcolor="#FCDFFF" cellspacing="0">
							<tr>
								<td width="50%" bgcolor="#4C7D7E" height="23">
									<b>
										<font color="#FFFFFF" size="2">
											<a>
												<xsl:attribute name="id"><xsl:value-of select="ADDITIONALDATA/@folder"/>\<xsl:value-of select="ADDITIONALDATA/@name"/></xsl:attribute>
												<xsl:attribute name="name"><xsl:value-of select="ADDITIONALDATA/@name"/></xsl:attribute>
												<xsl:value-of select="ADDITIONALDATA/@name"/>
											</a>
										</font>
									</b>
								</td>
								<td width="50%" bgcolor="#4C7D7E" height="23">
									<font color="#FFFFFF" size="1">
										<xsl:value-of select="ADDITIONALDATA/@folder"/>
									</font>
								</td>

							</tr>
							<tr>
								<td width="20%" bgcolor="#FFFFAA" valign="top">
									<font size="1">
										<xsl:value-of select="ADDITIONALDATA/@name"/>
									</font>
								</td>
								<td width="80%" bgcolor="#FFFFAA" valign="top">
									<font size="1">
										<xsl:value-of select="ADDITIONALDATA"/>
									</font>
								</td>

							</tr>
							<tr>
								<td colspan="1" bgcolor="#FFFFAA">
									<hr/>
								</td>
								<td bgcolor="#FFFFAA">
									<hr/>
								</td>
							</tr>
							</table>
					</xsl:for-each>		
										
					</xsl:for-each>
				</body>
			</html>
		</xsl:for-each>
	</xsl:template>
	
	<xsl:template match="FOLDER">
		<a>
			<xsl:attribute name="id">folder_<xsl:value-of select="@name"/></xsl:attribute>
			<xsl:attribute name="name"><xsl:value-of select="@name"/></xsl:attribute>
		</a>
		<table border="1" width="100%" bgcolor="#D2FDA8" cellspacing="0">
			<tr>
				<td>
					<table border="0" width="100%" bgcolor="#D2FDA8" cellspacing="0">
						<tr>
							<td bgcolor="#61B621" height="20">
								<b>
									<font size="2" color="#FFFFFF">
										<xsl:value-of select="@name"/>
									</font>
								</b>
							</td>
							<td bgcolor="#61B621" height="20">
								<p align="right">
									<b>
										<font color="#FFFFFF" size="1">
											<a>
												<xsl:attribute name="href">#folder_<xsl:value-of select="../@name"/></xsl:attribute>Up</a>
										</font>
									</b>
								</p>
							</td>
						</tr>
						</table>
						<table border="0" width="100%" bgcolor="#D2FDA8" cellspacing="0">
						<tr>
							<td bgcolor="#D2FDA8" colspan="2" height="15">
								<font size="1">
									<xsl:value-of select="DESCRIPTION"/>
								</font>
							</td>
						</tr>
						<tr>
							<td bgcolor="#D2FDA8" colspan="2" height="21">
								<hr/>
							</td>
						</tr>
						<tr>
							<td bgcolor="#D2FDA8" colspan="2" height="15">
								<font size="1">
									<b>Comment:</b>
									<xsl:value-of select="@comment"/>
								</font>
							</td>
						</tr>
						<tr>
							<td bgcolor="#D2FDA8" colspan="2" height="15">
								<font size="1"/>
							</td>
						</tr>
						<tr>
							<td width="100%" bgcolor="#D2FDA8" colspan="2" height="15">
								<table border="0" width="100%" cellspacing="0">
									<tr>
										<td>
											<font size="1">
												<b>Folders</b>
											</font>
										</td>
									</tr>
									<xsl:for-each select="FOLDER">
										<tr>
											<td>
												<font size="1">
													<a>
														<xsl:attribute name="href">#folder_<xsl:value-of select="@name"/></xsl:attribute>
														<xsl:value-of select="@name"/>
													</a>
												</font>
											</td>
										</tr>
									</xsl:for-each>
								</table>
								<table border="0" width="100%" cellspacing="0">
									<tr>
										<td width="66%">
											<font size="1">
												<b>Tests</b>
											</font>
										</td>
										<td width="33%">
											<font size="1">
												<b>&#160;</b>
											</font>
										</td>
									</tr>
									<xsl:for-each select="TEST">
										<tr>
											<td width="66%">
												<font size="1">
													<a>
														<xsl:attribute name="href">#<xsl:value-of select="@folder"/>\<xsl:value-of select="@name"/></xsl:attribute>
														<xsl:value-of select="@name"/>
													</a>
												</font>
											</td>
											<td width="33%">
												<font size="1">
													<xsl:apply-templates select="RUN/STATUS"/>
												</font>
											</td>
										</tr>
									</xsl:for-each>
								</table>
							</td>
						</tr>
						<tr>
							<td>
								<table border="0" width="100%" bgcolor="#D2FDA8" cellspacing="0">
									<tr>
										<td width="3%">&#160;</td>
										<td>
											<xsl:apply-templates/>
										</td>
									</tr>
								</table>
							</td>
						</tr>
					</table>
				</td>
			</tr>
		</table>
	</xsl:template>
	<xsl:template match="TESTLIST">
		<a>
			<xsl:attribute name="id"><xsl:value-of select="@name"/></xsl:attribute>
			<xsl:attribute name="name"><xsl:value-of select="@name"/></xsl:attribute>
		</a>
		<table border="0" width="100%" bgcolor="#D2FDA8" cellspacing="0">
			<tr>
			<td bgcolor="#7E587E" colspan="2" height="20">
					<b>
						<font size="2" color="#FFFFFF">
							<xsl:value-of select="@name"/>
						</font>
					</b>
				</td>
			</tr>
			
			<tr>
				<td width="100%" bgcolor="#ADDFFF" colspan="2" height="15">
					<table border="0" width="100%" cellspacing="0">
						<tr>
							<td width="77%">
								<font size="1">
									<b>Test:</b>
								</font>
							</td>
							<td width="23%">
								<font size="1">
									<b>Status:</b>
								</font>
							</td>
						</tr>
						<xsl:for-each select="TEST">
							<tr>
								<td width="77%">
									<font size="1">
										<a>
											<xsl:attribute name="href">#<xsl:value-of select="@folder"/>\<xsl:value-of select="@name"/></xsl:attribute>
											<xsl:value-of select="@name"/>
										</a>
									</font>
								</td>
								<td width="23%">
									<font size="1">
											<xsl:attribute name="STYLE">color:
			    								<xsl:choose>
			    								<xsl:when test="@status='Passed'">"#008000"</xsl:when>
			    								<xsl:when test="@status='Failed'">"#F00000"</xsl:when>
			    								<xsl:otherwise>"#000000"</xsl:otherwise>
			    								</xsl:choose></xsl:attribute>
											<xsl:value-of select="@status"/>
									</font>
								</td>
							</tr>
						</xsl:for-each>
					</table>
				</td>
			</tr>
		</table>
		<xsl:apply-templates select="TEST"/>
	</xsl:template>
	<xsl:template match="SUITES">
		<a>
			<xsl:attribute name="id"><xsl:value-of select="@name"/></xsl:attribute>
			<xsl:attribute name="name"><xsl:value-of select="@name"/></xsl:attribute>
		</a>
		<table border="0" width="100%" bgcolor="#D2FDA8" cellspacing="0">
			<tr>
				<td bgcolor="#61B621" colspan="2" height="20">
					<b>
						<font size="2" color="#FFFFFF">
							<xsl:value-of select="@name"/>
						</font>
					</b>
				</td>
			</tr>
			<tr>
				<td bgcolor="#D2FDA8" colspan="2" height="15">
					<font size="1">
						<xsl:value-of select="DESCRIPTION"/>
					</font>
				</td>
			</tr>
			<tr>
				<td bgcolor="#D2FDA8" colspan="2" height="21">
					<hr/>
				</td>
			</tr>

			<tr>
				<td bgcolor="#D2FDA8" colspan="2" height="15">
					<font size="1"/>
				</td>
			</tr>
			<tr>
				<td width="100%" bgcolor="#D2FDA8" colspan="2" height="15">
					<table border="0" width="100%" cellspacing="0">
						<tr>
							<td width="77%">
								<font size="1">
									<b>Test:</b>
								</font>
							</td>
							<td width="23%">
								<font size="1">
									<b>Status:</b>
								</font>
							</td>
						</tr>
						<xsl:for-each select="TEST">
							<tr>
								<td width="77%">
									<font size="1">
										<a>
											<xsl:attribute name="href">#<xsl:value-of select="@folder"/>\<xsl:value-of select="@name"/></xsl:attribute>
											<xsl:value-of select="@name"/>
										</a>
									</font>
								</td>
								<td width="23%">
									<font size="1">
											<xsl:attribute name="STYLE">color:
			    								<xsl:choose>
			    								<xsl:when test="@status='Passed'">"#008000"</xsl:when>
			    								<xsl:when test="@status='Failed'">"#F00000"</xsl:when>
			    								<xsl:otherwise>"#000000"</xsl:otherwise>
			    								</xsl:choose></xsl:attribute>
											<xsl:value-of select="@status"/>
										
									</font>
								</td>
							</tr>
						</xsl:for-each>
					</table>
				</td>
			</tr>
		</table>
	</xsl:template>	
	<xsl:template match="TEST">
		<!-- <p/> -->
		<table border="0" width="100%" bgcolor="#ECF5FF" cellspacing="0">
			<tr>
				<td width="50%" bgcolor="#C6AEC7" height="23">
					<b>
						<font color="#FFFFFF" size="1">
							<a>
								<xsl:attribute name="id"><xsl:value-of select="@folder"/>\<xsl:value-of select="@name"/></xsl:attribute>
								<xsl:attribute name="name"><xsl:value-of select="@name"/></xsl:attribute>
								<xsl:value-of select="@name"/>
							</a>
						</font>
					</b>
				</td>
				<td width="40%" bgcolor="#C6AEC7" height="23">
					<b>
					<font color="#FFFFFF" size="1">
						<xsl:value-of select="@folder"/>
					</font>
					</b>
				</td>
				<td width="10%" bgcolor="#C6AEC7" height="23">
					<p align="right">
						<b>
							<font color="#FFFFFF" size="1">
								<a>
									<xsl:attribute name="href">#<xsl:value-of select="../@name"/></xsl:attribute>Up</a>
							</font>
						</b>
					</p>
				</td>
			</tr>
		</table>
		<table border="0" width="100%" bgcolor="#D2FDA8" cellspacing="0">
			<tr>
				<td width="50%" height="12" bgcolor="#D5F1FF">
					<font size="1">
						<b>Executed On:</b>
						<xsl:value-of select="@creation_date"/>
					</font>
				</td>
				<td width="50%" height="12" bgcolor="#D5F1FF" colspan="2">
					<font size="1">
						<b>Execution Time:</b>
						<xsl:value-of select="@executedtime"/>
					</font>
				</td>
			</tr>

			<tr>
				<td width="50%" height="12" bgcolor="#D5F1FF">
					<font size="1">
						<b>Status: </b>
						<xsl:value-of select="@status"/>
					</font>
				</td>
				<td width="50%" height="12" bgcolor="#D5F1FF" colspan="2">
					<font size="1">
						<b/>
						
					</font>
				</td>
			</tr>
			<tr>
			</tr>
		</table>
		<table border="0" width="100%" bgcolor="#D2FDA8" cellspacing="0">
			<tr>
				<td width="100%" height="12" bgcolor="#D5F1FF" colspan="3"> </td>
			</tr>
			
			<xsl:for-each select="STEP">
			<tr>
				<td width="100%" colspan="3" bgcolor="#D5F1FF">
					
					<table border="0" width="100%" cellspacing="0">
						<tr>
						
							<td width="5%" bgcolor="#D5F1FF" valign="top">
								<font size="1">
									<b>Step:</b>
								</font>
						
							</td>
							
								<td width="40%" bgcolor="#D5F1FF" valign="top" align="left">
								
									<font size="1">
										<xsl:value-of select="@name"/>
									</font>
									
								</td>
							
							
							
							<td width="15%" bgcolor="#D5F1FF" valign="top" align="center">
								<font size="1">
									<b>Status:</b>
								</font>
							</td>
							

								<td width="40%" bgcolor="#D5F1FF" valign="top" align="center">
									<font size="1">
										<xsl:value-of select="STEPSTATUS"/>
									</font>
								</td>
						
						</tr>
						<tr>
							<td colspan="4">
								<!--<hr/>-->
							</td>
						</tr>
						
						<tr>
							<td width="100%" height="12" bgcolor="#D5F1FF" colspan="5"> </td>
						</tr>
					</table>
					
				</td>
			</tr>
		</xsl:for-each>
		</table>
	</xsl:template>
	
	<xsl:template match="STATUS">
					<font>
						<xsl:attribute name="STYLE">color:
			    <xsl:choose><xsl:when test="'Passed'">"#008000"</xsl:when><xsl:when test="STATUS='Failed'">"#F00000"</xsl:when><xsl:otherwise>"#000000"</xsl:otherwise></xsl:choose></xsl:attribute>
						<b>
							<xsl:value-of select="."/>
						</b>
					</font>
		</xsl:template>
		<xsl:template match="VERSTATUS">
					<font>
						<xsl:attribute name="STYLE">color:
			    <xsl:choose><xsl:when test="'Success'">"#008000"</xsl:when><xsl:when test="PROJECT/TESTLIST/TEST/VERIFIER/VERSTATUS ='Failed'">"#F00000"</xsl:when><xsl:otherwise>"#000000"</xsl:otherwise></xsl:choose></xsl:attribute>
						<b>
							<xsl:value-of select="."/>
						</b>
					</font>
		</xsl:template>
		<xsl:template match="PROJECT/TESTLIST/TEST/@status">
					<font>
						<xsl:attribute name="STYLE">color:
			    <xsl:choose><xsl:when test="'Passed'">"#008000"</xsl:when><xsl:when test="'Failed'">"#F00000"</xsl:when><xsl:otherwise>"#000000"</xsl:otherwise></xsl:choose></xsl:attribute>
						<b>
							<xsl:value-of select="."/>
						</b>
					</font>
		</xsl:template>
	
</xsl:stylesheet>
