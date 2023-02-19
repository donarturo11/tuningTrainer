#!/usr/bin/env bash
# https://stackoverflow.com/questions/35020236/creating-certificate-to-sign-gdb-on-mac-os-x-from-bash
PASSWORD=passwd
cat > myconfig.cnf << EOF

[ req ]
prompt             = no
distinguished_name = my dn
x509_extensions	   = v3_ca

[ my dn ]
# The bare minimum is probably a commonName
commonName = donarturo11.github.io
countryName = PL
localityName = Poland
organizationName = donarturo11 github
organizationalUnitName = SSL Dept.
stateOrProvinceName = YY
emailAddress = ssl-admin@example.com
name = donarturo11
dnQualifier = some

[ v3_ca ]
subjectKeyIdentifier=hash
authorityKeyIdentifier=keyid:always,issuer:always
basicConstraints = CA:true

[ my server exts ]
basicConstraints=CA:FALSE
keyUsage = nonRepudiation, digitalSignature, keyEncipherment
extendedKeyUsage = codeSigning
subjectKeyIdentifier=hash
authorityKeyIdentifier=keyid,issuer
nsCertType = client, email, objsign

EOF

echo "generating the private key ..."
openssl genrsa -des3 -passout pass:$PASSWORD -out server.key 2048

echo ""
echo "generating the CSR (certificate signing request) ..."
openssl req -new -passin pass:$PASSWORD -passout pass:$PASSWORD -key server.key \
            -out server.csr -config myconfig.cnf -extensions 'my server exts'

echo ""
echo "generating the self-signed certificate ..."
openssl x509 -req -passin pass:$PASSWORD -days 365 -in server.csr -signkey server.key \
        -out server.crt -extfile myconfig.cnf -extensions 'my server exts'

echo ""
echo "convert crt + RSA private key into a PKCS12 (PFX) file ..."
openssl pkcs12 -export -passin pass:$PASSWORD -passout pass:$PASSWORD \
        -in server.crt -inkey server.key -out server.pfx

echo ""
echo "importing the certificate ..."
sudo security import server.pfx -k /Library/Keychains/System.keychain -P $PASSWORD
sudo security unlock -k /Library/Keychains/System.keychain
